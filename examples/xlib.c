#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

#include <X11/Xlib.h>

#include "yarl.h"
#include "backend/xlib.h"

int main(void) {

    Yarl yarl = yarl_init(500, 500);

    Display *dpy = XOpenDisplay(NULL);
    assert(dpy != NULL);

    Window root = XDefaultRootWindow(dpy);
    GC gc = XCreateGC(dpy, root, 0, NULL);
    Window win = XCreateSimpleWindow(dpy, root, 0, 0, 500, 500, 5, 0, 0);

    XMapRaised(dpy, win);

    XEvent ev = { 0 };
    bool quit = false;
    while (!quit) {

        if (XPending(dpy)) {
            XNextEvent(dpy, &ev);
            XClearWindow(dpy, win);
            switch (ev.type) {
                // TODO: window attribute
                case KeyPress: {
                    quit = true;
                } break;
            }
        }
        else {
            yarl_render_xlib(yarl, dpy, win, gc);
        }

    }

    XCloseDisplay(dpy);
    yarl_destroy(yarl);
}
