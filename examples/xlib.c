#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

#include "examples.c"

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "yarl.h"

int main(void) {

    Yarl *yarl = yarl_init(500, 500);
    assert(yarl != NULL);
    triangles(yarl);

    Display *dpy = XOpenDisplay(NULL);
    assert(dpy != NULL);

    Window root = XDefaultRootWindow(dpy);
    GC gc = XCreateGC(dpy, root, 0, NULL);
    Window win = XCreateSimpleWindow(dpy, root, 0, 0, 500, 500, 0, 0, 0);
    XSelectInput(dpy, win, KeyPressMask | ExposureMask);

    XMapRaised(dpy, win);

    XEvent ev = { 0 };
    bool quit = false;
    while (!quit) {

        int w = yarl_get_width(yarl);
        int h = yarl_get_height(yarl);

        for (int y=0; y < h; ++y) {
            for (int x=0; x < w; ++x) {
                YarlColor color = yarl_get_pixel(yarl, x, y);
                // reversing byte order
                // YarlColor rev = YARL_COLOR(color.b, color.g, color.r, color.a);
                XSetForeground(dpy, gc, *(uint32_t*) &color);
                XFillRectangle(dpy, win, gc, x, y, 1, 1);

            }
        }

        XNextEvent(dpy, &ev);
        XClearWindow(dpy, win);

        switch (ev.type) {
            case KeyPress: {
                uint32_t keycode = ev.xkey.keycode;
                if (keycode == 0x9 || keycode == 0x18)
                    quit = true;
            } break;

        }

    }

    XCloseDisplay(dpy);
    yarl_destroy(yarl);
}
