#include "yarl.h"

#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <sys/param.h>

#define CLAMP(value, min, max) \
    (assert(min <= max), \
    (value) > (max) ? (max) : (value) < (min) ? (min) : (value))

struct YarlCanvas {
    int width, height;
    color_t **canvas;
};

Yarl yarl_canvas_create(int width, int height) {

    Yarl yarl = malloc(sizeof(struct YarlCanvas));
    yarl->width  = width;
    yarl->height = height;
    yarl->canvas = NULL;

    yarl->canvas = malloc(yarl->height * sizeof(color_t*));
    for (int y=0; y < yarl->height; ++y)
        yarl->canvas[y] = calloc(yarl->width, sizeof(color_t));

    return yarl;
}

color_t **yarl_get_canvas(const Yarl yarl) {
    return yarl->canvas;
}

int yarl_get_canvas_width(const Yarl yarl) {
    return yarl->width;
}

int yarl_get_canvas_height(const Yarl yarl) {
    return yarl->height;
}

void yarl_canvas_destroy(Yarl yc) {
    for (int y=0; y < yc->height; ++y)
        free(yc->canvas[y]);
    free(yc->canvas);
}

void clear(Yarl yarl, color_t color) {
    for (int y=0; y < yarl->height; ++y)
        for (int x=0; x < yarl->height; ++x)
            yarl->canvas[y][x] = color;
}

// TODO point()

void rect(Yarl yarl, int x, int y, int w, int h, color_t color) {
    for (int i=y; i < y+h; ++i)
        for (int j=x; j < x+w; ++j)
            yarl->canvas[i][j] = color;
}

void circle(Yarl yarl, int cx, int cy, int r, color_t color) {

    int x0 = CLAMP(cx - r, 0, yarl->width);
    int y0 = CLAMP(cy - r, 0, yarl->height);
    int x1 = CLAMP(cx + r, 0, yarl->width);
    int y1 = CLAMP(cy + r, 0, yarl->height);

    for (int y=y0; y < y1; ++y) {
        for (int x=x0; x < x1; ++x) {

            double dist = (cx - x) * (cx - x) + (cy - y) * (cy - y);

            if (dist < r*r)
                yarl->canvas[y][x] = color;
        }
    }

}

void line(Yarl yarl, int x0, int y0, int x1, int y1, color_t color) {

    float dy = y1 - y0;
    float dx = x1 - x0;
    float m  = dy / dx;
    int start = MIN(x0, x1);

    for (float x=start; x < start + fabsf(dx); ++x) {
        float y = m * (x - x0) + y0;
        yarl->canvas[(size_t)y][(size_t)x] = color;
    }

}
