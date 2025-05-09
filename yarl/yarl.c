#include "yarl.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <sys/param.h>

// #define YARL_DEBUG

#define CLAMP(value, min, max) \
    (assert(min <= max), \
    (value) > (max) ? (max) : (value) < (min) ? (min) : (value))


#ifdef YARL_DEBUG
#define CHECK(cond, message, ...) \
    if (!(cond)) { \
        printf("-- YARL ERROR --\n"); \
        printf("at: `%s`\n", __func__); \
        printf("cause: " message __VA_OPT__(,) __VA_ARGS__); \
        exit(EXIT_FAILURE); \
    }
#else
#define CHECK(...)
#endif // YARL_DEBUG


struct YarlContext {
    int width, height;
    YarlColor **canvas;
};

Yarl yarl_init(int width, int height) {

    Yarl yarl = malloc(sizeof(struct YarlContext));
    yarl->width  = width;
    yarl->height = height;
    yarl->canvas = NULL;

    yarl->canvas = malloc(yarl->height * sizeof(YarlColor*));
    for (int y=0; y < yarl->height; ++y)
        yarl->canvas[y] = calloc(yarl->width, sizeof(YarlColor));

    return yarl;
}

YarlColor yarl_get_pixel(const Yarl yarl, int x, int y) {
    return yarl->canvas[y][x];
}

int yarl_get_width(const Yarl yarl) {
    return yarl->width - 1;
}

int yarl_get_height(const Yarl yarl) {
    return yarl->height - 1;
}

void yarl_destroy(Yarl yc) {
    for (int y=0; y < yc->height; ++y)
        free(yc->canvas[y]);
    free(yc->canvas);
}

void yarl_clear(Yarl yarl, YarlColor color) {
    yarl_draw_rect(yarl, 0, 0, yarl->width, yarl->height, color);
}

void yarl_draw_point(Yarl yarl, int x, int y, YarlColor color) {
    CHECK(y < yarl->height, "Index `y` is out of bounds\ny = %d\nheight = %d\n", y, yarl->height);
    CHECK(x < yarl->width, "Index `x` is out of bounds\ny = %d\nwidth = %d\n", x, yarl->width);

    yarl->canvas[y][x] = color;
}

void yarl_draw_rect_outline(Yarl yarl, int x, int y, int w, int h, YarlColor color) {

    yarl_draw_line(yarl, x, y, x+w, y, color);
    yarl_draw_line(yarl, x, y, x, y+h, color);
    yarl_draw_line(yarl, x+w, y, x+w, y+h, color);
    yarl_draw_line(yarl, x, y+h, x+w, y+h, color);

    // for (int i=y; i < y+h; ++i) {
    //     if (i == y || i == y+h-1) {
    //         for (int j=x; j < x+w; ++j)
    //             yarl_draw_point(yarl, j, i, color);
    //     } else {
    //         yarl_draw_point(yarl, x, i, color);
    //         yarl_draw_point(yarl, x+w, i, color);
    //     }
    // }

}

void yarl_draw_rect(Yarl yarl, int x, int y, int w, int h, YarlColor color) {

#ifdef YARL_DEBUG
    yarl_draw_circle(yarl, x, y, 3, color);
    yarl_draw_circle(yarl, x+w, y, 3, color);
    yarl_draw_circle(yarl, x, y+h, 3, color);
    yarl_draw_circle(yarl, x+h, y+h, 3, color);
#endif // YARL_DEBUG

    for (int i=y; i < y+h; ++i)
        for (int j=x; j < x+w; ++j)
            yarl_draw_point(yarl, j, i, color);
}

// TODO: too slow
void yarl_draw_circle_outline(Yarl yarl, int cx, int cy, int r, YarlColor color) {

    // TODO: debug

    int x0 = CLAMP(cx - r, 0, yarl->width);
    int y0 = CLAMP(cy - r, 0, yarl->height);
    int x1 = CLAMP(cx + r, 0, yarl->width);
    int y1 = CLAMP(cy + r, 0, yarl->height);

    for (int y=y0; y < y1; y += 1) {
        for (int x=x0; x < x1; x += 1) {

            double dist = (cx - x) * (cx - x) + (cy - y) * (cy - y);

            if (dist == r*r)
                yarl_draw_point(yarl, x, y, color);
        }
    }

}

void yarl_draw_circle(Yarl yarl, int cx, int cy, int r, YarlColor color) {

    // TODO: debug

    int x0 = CLAMP(cx - r, 0, yarl->width);
    int y0 = CLAMP(cy - r, 0, yarl->height);
    int x1 = CLAMP(cx + r, 0, yarl->width);
    int y1 = CLAMP(cy + r, 0, yarl->height);

    for (int y=y0; y < y1; ++y) {
        for (int x=x0; x < x1; ++x) {

            double dist = (cx - x) * (cx - x) + (cy - y) * (cy - y);

            if (dist < r*r)
                yarl_draw_point(yarl, x, y, color);
        }
    }

}

// TODO:
void yarl_draw_ellipse(Yarl yarl, int cx, int cy, int rx, int ry, YarlColor color) {

    int x0 = CLAMP(cx - rx, 0, yarl->width);
    int y0 = CLAMP(cy - ry, 0, yarl->height);
    int x1 = CLAMP(cx + rx, 0, yarl->width);
    int y1 = CLAMP(cy + ry, 0, yarl->height);

#ifdef YARL_DEBUG
    yarl_draw_rect_outline(yarl, x0, y0, x1-x0, y1-y0, color);
#endif // YARL_DEBUG


    for (int y=y0; y < y1; ++y) {
        for (int x=x0; x < x1; ++x) {
            yarl_draw_point(yarl, x, y, color);
        }
    }

}

void yarl_draw_line(Yarl yarl, int x0, int y0, int x1, int y1, YarlColor color) {
    yarl_draw_line_thick(yarl, x0, y0, x1, y1, color, 1);
}

void yarl_draw_line_thick(Yarl yarl, int x0, int y0, int x1, int y1, YarlColor color, int thickness) {

    float dy = y1 - y0;
    float dx = x1 - x0;

#ifdef YARL_DEBUG
    yarl_draw_circle(yarl, x1, y1, 3, color);
    yarl_draw_circle(yarl, x0, y0, 3, color);
#endif // YARL_DEBUG

    // avoid divide-by-zero errors
    if (dx == 0) {
        for (float y=y0; y < y1; ++y)
            yarl_draw_circle(yarl, x0, y, thickness, color);
        return;
    }

    float m = dy / dx;
    // the needed precision for rendering lines
    float step = fabsf(dx / yarl->width);
    int start = MIN(x0, x1);

    for (float x=start; x < start + fabsf(dx); x += step) {
        float y = m * (x - x0) + y0;
        yarl_draw_circle(yarl, x, y, thickness, color);
    }

}

void yarl_draw_triangle_outline(
    Yarl yarl,
    int x0, int y0,
    int x1, int y1,
    int x2, int y2,
    YarlColor color
) {

    yarl_draw_line(yarl, x0, y0, x1, y1, color);
    yarl_draw_line(yarl, x0, y0, x2, y2, color);
    yarl_draw_line(yarl, x1, y1, x2, y2, color);

}
