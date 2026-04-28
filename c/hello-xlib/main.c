#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <xcb/xcb.h>

int main(int argc, char** argv)
{
  Display* dpy = XOpenDisplay(0);
  Window root = XDefaultRootWindow(dpy);

  int x = 0;
  int y = 0;
  int w = 800;
  int h = 600;
  int wborder = 0;
  int wdepth = CopyFromParent;
  int wclass = CopyFromParent;
  Visual* wvisual = CopyFromParent;

  int attr_mask = CWEventMask | CWBackPixel | CWOverrideRedirect;
  XSetWindowAttributes win_attr = {};
  win_attr.background_pixel = 0xffffff;
  win_attr.override_redirect = 0;
  Window win_main = XCreateWindow(dpy, root, x, y, w, h, wborder, wdepth, wclass, wvisual, attr_mask, &win_attr);
  XMapWindow(dpy, root);

  for (;;) {
    XEvent event = {};
    XNextEvent(dpy, &event);
  }
}
