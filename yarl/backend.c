#include "yarl.h"

#ifdef YARL_BACKEND_RAYLIB

#include <raylib.h>

void render_raylib(Yarl yarl, int x0, int y0, float scale) {
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
#include <stdint.h>

int render_ppm(Yarl yarl, const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (f == NULL)
        return -1;

    int w = yarl_get_width(yarl);
    int h = yarl_get_height(yarl);
    fprintf(f, "P6 %d %d %d\n", w, h, 255);

    for (int y=0; y < h; ++y) {
        for (int x=0; x < w; ++x) {
            YarlColor color = yarl_get_pixel(yarl, x, y);
            fwrite(&color, 3, 1, f);
        }
    }

    fclose(f);
    return 0;
}

#endif // YARL_BACKEND_PPM
