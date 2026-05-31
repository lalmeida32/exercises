#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define _DEFAULT_SCREEN 0
#define _ESC_KEYCODE 0x09

Window _CreateWindow(Display *display);
void _DrawStrings(Display *display, Drawable window, GC gc);
void _KeyPress(XEvent *pevent);
void _KeyRelease(XEvent *pevent, Display *dis);

int main(void)
{
  Display *dis = XOpenDisplay(NULL);
  Window win = _CreateWindow(dis);
  XSelectInput(dis, win, KeyPressMask | KeyReleaseMask | ExposureMask);
  XMapWindow(dis, win);
  XFlush(dis);

  GC gc = XCreateGC(dis, win, 0L, NULL);
  XFontStruct *font = XLoadQueryFont(dis, "lucidasanstypewriter-bold-14");
  XSetFont(dis, gc, font->fid);

  XEvent event;
  while (True)
  {
    XNextEvent(dis, &event);

    if (event.xkey.keycode == _ESC_KEYCODE)
      break;

    switch (event.type)
    {
    case KeyPress:
      _KeyPress(&event);
      break;
    case KeyRelease:
      _KeyRelease(&event, dis);
    case Expose:
      XClearWindow(dis, win);
      _DrawStrings(dis, win, gc);
    }
  }

  XFreeFont(dis, font);
  XFreeGC(dis, gc);
  XDestroyWindow(dis, win);
  XCloseDisplay(dis);
  return 0;
}

Window _CreateWindow(Display *display)
{
  Window parent = RootWindow(display, _DEFAULT_SCREEN);
  int x = 0, y = 0;
  unsigned int width = 500, height = 200;
  unsigned int border_width = 0;
  int depth = CopyFromParent;
  unsigned int class = InputOutput;
  Visual *visual = CopyFromParent;
  unsigned long valuemask = CWBackPixel | CWBorderPixel;
  XSetWindowAttributes attributes;
  attributes.background_pixel = WhitePixel(display, _DEFAULT_SCREEN);
  attributes.border_pixel = BlackPixel(display, _DEFAULT_SCREEN);
  return XCreateWindow(
      display, parent, x, y, width, height, border_width, depth, class, visual,
      valuemask, &attributes);
}

void _DrawStrings(Display *display, Drawable window, GC gc)
{
  int x = 32, y = 92;
  char *string = "Focus this window and press any key.";
  int length = strlen(string);
  XDrawString(display, window, gc, x, y, string, length);

  x = 42, y = 112;
  string = "Check console output. ESC to quit.";
  length = strlen(string);
  XDrawString(display, window, gc, x, y, string, length);
}

void _KeyPress(XEvent *pevent)
{
  XEvent event = *pevent;
  printf("Key #%ld was pressed.\n", (long)XLookupKeysym(&event.xkey, 0));
}

void _KeyRelease(XEvent *pevent, Display *dis)
{
  XEvent event = *pevent;

  if (XEventsQueued(dis, QueuedAfterReading))
  {
    XEvent nev;
    XPeekEvent(dis, &nev);

    if (nev.type == KeyPress && nev.xkey.keycode == event.xkey.keycode)
    {
      XNextEvent(dis, &event);
      return;
    }
  }

  printf("key #%ld was released.\n", (long)XLookupKeysym(&event.xkey, 0));
}