#include <yarl.h>

#include <X11/Xlib.h>

static inline void yarl_render_xlib(Yarl yarl, Display *dpy, Window win, GC gc) {
    int w = yarl_get_width(yarl);
    int h = yarl_get_height(yarl);

    for (int y=0; y < h; ++y) {
        for (int x=0; x < w; ++x) {
            YarlColor color = yarl_get_pixel(yarl, x, y);

            // reverse byte order
            YarlColor c =
                ((color & 0x000000ff) >> 3*8) |
                ((color & 0x0000ff00) << 1*8) |
                ((color & 0x00ff0000) >> 1*8) |
                color >> 3*8;

            XSetForeground(dpy, gc, c);
            XFillRectangle(dpy, win, gc, x, y, 1, 1);

        }
    }

}
