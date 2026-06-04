FROM python:3.13.13-trixie@sha256:d8f365c785cfb92d0f74f74b50b4c356f53bdb395878d438e0a58b0bd028c182

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    xmlsec1 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=ghcr.io/astral-sh/uv:0.11.18-python3.13-trixie-slim@sha256:09fdd532aaaca60cf5159276003139650585cf7612193a84dfbc2f0d3c4b7ce8 \
  /usr/local/bin/uv \
  /usr/local/bin/uvx \
  /usr/local/bin/

ENV UV_PROJECT_ENVIRONMENT=/opt/venv
ENV UV_LINK_MODE=copy
ENV PATH="/opt/venv/bin:$PATH"

COPY pyproject.toml uv.lock ./

RUN --mount=type=cache,target=/root/.cache/uv \
  uv sync --locked --no-install-project

COPY . .

EXPOSE 8000

CMD ["flask", "--app", "app:app", "run", "--host", "0.0.0.0", "--port", "8000", "--debug"]

