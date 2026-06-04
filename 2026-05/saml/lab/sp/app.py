import base64
import logging
import zlib
from pprint import pformat
from urllib.parse import parse_qs, urlparse

from flask import Flask, Response, redirect, request, session

from saml2 import BINDING_HTTP_POST, BINDING_HTTP_REDIRECT
from saml2.client import Saml2Client
from saml2.config import Config as Saml2Config
from saml2.saml import NAMEID_FORMAT_EMAILADDRESS
from saml2.sigver import get_xmlsec_binary


# -----------------------------------------------------------------------------
# Minimal lab config
# -----------------------------------------------------------------------------

BASE_URL = "http://localhost:8000"

SP_ENTITY_ID = f"{BASE_URL}/metadata"
ACS_URL = f"{BASE_URL}/acs"

IDP_METADATA_URL = "http://keycloak:8080/realms/employees/protocol/saml/descriptor"

app = Flask(__name__)
app.secret_key = "dev-only-secret"

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger("saml-lab")


# -----------------------------------------------------------------------------
# Helpers
# -----------------------------------------------------------------------------

def decode_redirect_saml_request(value: str) -> str:
    compressed = base64.b64decode(value)
    return zlib.decompress(compressed, -15).decode("utf-8")


def decode_post_saml_response(value: str) -> str:
    return base64.b64decode(value).decode("utf-8")


def saml_client() -> Saml2Client:
    config = {
        "entityid": SP_ENTITY_ID,
        "metadata": {
            "remote": [
                {
                    "url": IDP_METADATA_URL,
                }
            ]
        },
        "service": {
            "sp": {
                "name": "Minimal PySAML2 Flask SP",
                "endpoints": {
                    "assertion_consumer_service": [
                        (ACS_URL, BINDING_HTTP_POST),
                    ],
                },

                "authn_requests_signed": False,
                "want_response_signed": False,
                "want_assertions_signed": False,

                "allow_unsolicited": False,
                "name_id_format": [NAMEID_FORMAT_EMAILADDRESS],
            }
        },

        "debug": 1,

        "xmlsec_binary": get_xmlsec_binary([
            "/usr/bin/xmlsec1",
            "/usr/local/bin/xmlsec1",
            "/opt/homebrew/bin/xmlsec1",
        ]),
    }

    sp_config = Saml2Config()
    sp_config.load(config)

    sp_config.allow_unknown_attributes = True

    return Saml2Client(config=sp_config)


def make_sp_metadata() -> str:
    return f"""<?xml version="1.0"?>
<md:EntityDescriptor
    xmlns:md="urn:oasis:names:tc:SAML:2.0:metadata"
    entityID="{SP_ENTITY_ID}">
  <md:SPSSODescriptor
      protocolSupportEnumeration="urn:oasis:names:tc:SAML:2.0:protocol"
      AuthnRequestsSigned="false"
      WantAssertionsSigned="false">
    <md:NameIDFormat>{NAMEID_FORMAT_EMAILADDRESS}</md:NameIDFormat>
    <md:AssertionConsumerService
        Binding="{BINDING_HTTP_POST}"
        Location="{ACS_URL}"
        index="0"
        isDefault="true"/>
  </md:SPSSODescriptor>
</md:EntityDescriptor>
"""


# -----------------------------------------------------------------------------
# Routes
# -----------------------------------------------------------------------------

@app.route("/")
def index():
    if "saml_user" not in session:
        return """
        <h1>Minimal SAML SP</h1>
        <p>Status: not logged in</p>
        <p><a href="/login">Login with SAML</a></p>
        <p><a href="/metadata">View SP metadata</a></p>
        """

    return f"""
    <h1>Minimal SAML SP</h1>
    <p>Status: logged in</p>
    <p><strong>NameID:</strong> {session.get("name_id")}</p>
    <p><a href="/me">View SAML user data</a></p>
    <p><a href="/logout">Logout locally</a></p>
    """


@app.route("/metadata")
def metadata():
    return Response(make_sp_metadata(), mimetype="text/xml")


@app.route("/login")
def login():
    client = saml_client()

    reqid, info = client.prepare_for_authenticate(
        binding=BINDING_HTTP_REDIRECT,
        relay_state=BASE_URL + "/me",
    )

    headers = dict(info["headers"])
    location = headers["Location"]

    session["outstanding_queries"] = {reqid: BASE_URL + "/me"}

    logger.info("SAML AuthnRequest ID: %s", reqid)
    logger.info("Redirecting to IdP: %s", location)

    parsed = urlparse(location)
    params = parse_qs(parsed.query)
    saml_request = params.get("SAMLRequest", [None])[0]

    if saml_request:
        try:
            logger.info(
                "\n========== OUTGOING SAMLRequest ==========\n%s\n",
                decode_redirect_saml_request(saml_request),
            )
        except Exception:
            logger.exception("Could not decode SAMLRequest")

    return redirect(location)


@app.route("/acs", methods=["POST"])
def acs():
    if "SAMLResponse" not in request.form:
        return Response("Missing SAMLResponse", status=400)

    raw_response = request.form["SAMLResponse"]

    logger.info("ACS received POST from IdP")
    logger.info("POST keys: %s", list(request.form.keys()))
    logger.info("RelayState: %s", request.form.get("RelayState"))

    try:
        logger.info(
            "\n========== INCOMING SAMLResponse ==========\n%s\n",
            decode_post_saml_response(raw_response),
        )
    except Exception:
        logger.exception("Could not decode SAMLResponse")

    client = saml_client()

    try:
        authn_response = client.parse_authn_request_response(
            raw_response,
            BINDING_HTTP_POST,
            outstanding=session.get("outstanding_queries", {}),
        )
    except Exception as exc:
        logger.exception("SAML validation failed")
        return Response(f"SAML validation failed:\n{exc}", status=400)

    if not authn_response:
        return Response("Bad SAMLResponse", status=400)

    attributes = authn_response.get_identity()
    subject = authn_response.get_subject()
    name_id = subject.text if subject is not None else None

    session["saml_user"] = attributes
    session["name_id"] = name_id
    session.pop("outstanding_queries", None)

    logger.info("Authenticated NameID: %s", name_id)
    logger.info("Attributes:\n%s", pformat(attributes))

    return redirect(request.form.get("RelayState") or "/")


@app.route("/me")
def me():
    if "saml_user" not in session:
        return redirect("/")

    return Response(
        pformat(
            {
                "name_id": session.get("name_id"),
                "attributes": session.get("saml_user"),
            }
        ),
        mimetype="text/plain",
    )


@app.route("/logout")
def logout():
    session.clear()
    return redirect("/")


