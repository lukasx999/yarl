#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include <X11/Xlib.h>

#define YARL_BACKEND_XLIB
#include <yarl.h>
#include <backend/xlib.h>



void draw(Yarl yarl) {

    int h = yarl_get_height(yarl);
    int w = yarl_get_width(yarl);
    int size = 100;

    yarl_fill(yarl, YARL_GREY);
    yarl_draw_rect(yarl, w/2-size, h/2-size, size, size, YARL_BLUE);
    yarl_draw_circle(yarl, w/2, h/2, 50, YARL_RED);
}


int main(void) {

    Yarl yarl = yarl_init(500, 500);
    draw(yarl);


    Display *dpy = XOpenDisplay(NULL);
    assert(dpy != NULL);


    Window root = XDefaultRootWindow(dpy);
    int scr = XDefaultScreen(dpy);
    GC gc = XCreateGC(dpy, root, 0, NULL);
    Window win = XCreateSimpleWindow(dpy, root, 0, 0, 500, 500, 5, 0, 0);
    Colormap cmap = XDefaultColormap(dpy, scr);


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

    return 0;
}
