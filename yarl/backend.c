#include "yarl.h"


// TODO: get view into entire canvas instead of iterating

// TODO: OpenGL
// TODO: Xlib
// TODO: Wayland



#ifdef YARL_BACKEND_RAYLIB

#include <raylib.h>

void yarl_render_raylib(Yarl yarl, int x0, int y0, float scale) {
    for (int y=0; y < yarl_get_height(yarl); ++y) {
        for (int x=0; x < yarl_get_width(yarl); ++x) {
            Color color = GetColor(yarl_get_pixel(yarl, x, y));
            DrawRectangle(
                x0 + x * scale,
                y0 + y * scale,
                scale,
                scale,
                color
            );
        }
    }
}

#endif // YARL_BACKEND_RAYLIB



#ifdef YARL_BACKEND_PPM

#include <stdio.h>
#include <stdlib.h>

int yarl_render_ppm(Yarl yarl, const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (f == NULL)
        return -1;

    int w = yarl_get_width(yarl);
    int h = yarl_get_height(yarl);
    fprintf(f, "P6 %d %d %d\n", w, h, 255);

    for (int y=0; y < h; ++y) {
        for (int x=0; x < w; ++x) {
            YarlColor color = yarl_get_pixel(yarl, x, y);

            // reverse byte order
            YarlColor c =
                ((color & 0x000000ff) >> 3*8) |
                ((color & 0x0000ff00) << 1*8) |
                ((color & 0x00ff0000) >> 1*8) |
                color >> 3*8;

            fwrite(&c, 3, 1, f);
        }
    }

    fclose(f);
    return 0;
}

#endif // YARL_BACKEND_PPM
