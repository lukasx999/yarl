#ifndef _YARL_BACKEND_H
#define _YARL_BACKEND_H

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "yarl.h"

#include <raylib.h>



// TODO: get view into entire canvas instead of iterating



#define PIXEL_SIZE 1

static inline void render_raylib(Yarl yarl) {
    for (int y=0; y < yarl_get_height(yarl); ++y) {
        for (int x=0; x < yarl_get_width(yarl); ++x) {
            Color color = GetColor(yarl_get_pixel(yarl, x, y));
            DrawRectangle(
                x*PIXEL_SIZE,
                y*PIXEL_SIZE,
                PIXEL_SIZE,
                PIXEL_SIZE,
                color
            );
        }
    }
}

static inline void render_ppm(Yarl yarl, const char *filename) {
    FILE *f = fopen(filename, "wb");
    assert(f != NULL);

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
}

#endif // _YARL_BACKEND_H
