#include "yarl.h"

#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <sys/param.h>

#include "util.h"


struct YarlContext {
    int width, height;
    YarlColor **canvas;
};

// TODO: let the user pass in their own buffer
Yarl yarl_init(int width, int height) {

    Yarl yarl = malloc(sizeof(struct YarlContext));
    if (yarl == NULL)
        return NULL;

    yarl->width  = width;
    yarl->height = height;
    yarl->canvas = NULL;

    yarl->canvas = malloc(yarl->height * sizeof(YarlColor*));
    if (yarl->canvas == NULL)
        return NULL;

    for (int y=0; y < yarl->height; ++y) {
        yarl->canvas[y] = calloc(yarl->width, sizeof(YarlColor));
        if (yarl->canvas[y] == NULL)
            return NULL;
    }

    return yarl;
}

YarlColor yarl_get_pixel(const Yarl yarl, int x, int y) {
    assert(x < yarl->width);
    assert(y < yarl->height);
    return yarl->canvas[y][x];
}

YarlColor **yarl_get_canvas(const Yarl yarl) {
    return yarl->canvas;
}

int yarl_get_width(const Yarl yarl) {
    return yarl->width - 1;
}

int yarl_get_height(const Yarl yarl) {
    return yarl->height - 1;
}

void yarl_destroy(Yarl yarl) {
    for (int y=0; y < yarl->height; ++y)
        free(yarl->canvas[y]);
    free(yarl->canvas);
}

void yarl_fill(Yarl yarl, YarlColor color) {
    yarl_draw_rect(yarl, 0, 0, yarl->width, yarl->height, color);
}

void yarl_draw_point(Yarl yarl, int x, int y, YarlColor color) {
    yarl->canvas[y][x] = color;
}

void yarl_draw_rect_outline(Yarl yarl, int x, int y, int w, int h, YarlColor color) {

    for (int i=y; i < y+h; ++i) {
        if (i == y || i == y+h-1) {
            for (int j=x; j < x+w; ++j)
                yarl_draw_point(yarl, j, i, color);
        } else {
            yarl_draw_point(yarl, x, i, color);
            yarl_draw_point(yarl, x+w, i, color);
        }
    }

}

void yarl_draw_rect(Yarl yarl, int x, int y, int w, int h, YarlColor color) {
    for (int i=y; i < y+h; ++i)
        for (int j=x; j < x+w; ++j)
            yarl_draw_point(yarl, j, i, color);
}

void yarl_draw_arc_outline(Yarl yarl, int cx, int cy, int r, float start_angle, float rot_count, YarlColor color) {

    start_angle = fmodf(start_angle, 360);

    if (start_angle < 0.)
        start_angle = 360. - fabsf(start_angle);

    for (float a=start_angle; a < start_angle + rot_count; ++a) {
        int x = cx + r * cos(YARL_DEG_TO_RAD(a));
        int y = cy + r * sin(YARL_DEG_TO_RAD(a));
        yarl_draw_point(yarl, x, y, color);
    }

}

void yarl_draw_arc(
    Yarl yarl,
    int cx,
    int cy,
    int r,
    float start_angle,
    float rot_count,
    YarlColor color
) {

    start_angle = fmodf(start_angle, 360.);

    if (start_angle < 0.)
        start_angle = 360. - fabsf(start_angle);

    int x0 = YARL_CLAMP(cx - r, 0, yarl->width);
    int y0 = YARL_CLAMP(cy - r, 0, yarl->height);
    int x1 = YARL_CLAMP(cx + r, 0, yarl->width);
    int y1 = YARL_CLAMP(cy + r, 0, yarl->height);

    for (int x=x0; x < x1; ++x) {
        for (int y=y0; y < y1; ++y) {

            // position relative to arc middle
            int mx = x - cx;
            int my = cy - y;

            float angle = rotation_angle_around_center(mx, my);

            for (float a=start_angle; a < start_angle + rot_count; ++a) {

                // coordinates of arc outline
                int xo = r * cos(YARL_DEG_TO_RAD(a));
                int yo = r * sin(YARL_DEG_TO_RAD(a));

                int leno = xo*xo + yo*yo;
                int len  = mx*mx + my*my;

                if (angle == a && len < leno)
                    yarl_draw_point(yarl, x, y, color);

            }

        }
    }

}

void yarl_draw_circle_outline(Yarl yarl, int cx, int cy, int r, YarlColor color) {
    yarl_draw_arc_outline(yarl, cx, cy, r, 0, 360, color);
}

void yarl_draw_circle(Yarl yarl, int cx, int cy, int r, YarlColor color) {

    int x0 = YARL_CLAMP(cx - r, 0, yarl->width);
    int y0 = YARL_CLAMP(cy - r, 0, yarl->height);
    int x1 = YARL_CLAMP(cx + r, 0, yarl->width);
    int y1 = YARL_CLAMP(cy + r, 0, yarl->height);

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
    assert(!"TODO");
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

static inline float triangle_edge_function(int x0, int y0, int x1, int y1, int x2, int y2) {
    return (x1-x0) * (y2-y0) - (y1-y0) * (x2-x0);
}

void yarl_draw_triangle(Yarl yarl, int x0, int y0, int x1, int y1, int x2, int y2, YarlColor color) {

    int h = yarl_get_height(yarl);
    int w = yarl_get_width(yarl);

    // bounding box of triangle
    int xs = YARL_CLAMP(MIN(x0, MIN(x1, x2)), 0, w);
    int xe = YARL_CLAMP(MAX(x0, MAX(x1, x2)), 0, w);
    int ys = YARL_CLAMP(MIN(y0, MIN(y1, y2)), 0, h);
    int ye = YARL_CLAMP(MAX(y0, MAX(y1, y2)), 0, h);

    for (int y=ys; y < ye; ++y) {
        for (int x=xs; x < xe; ++x) {

            float area1 = triangle_edge_function(x0, y0, x1, y1, x, y);
            float area2 = triangle_edge_function(x1, y1, x2, y2, x, y);
            float area3 = triangle_edge_function(x2, y2, x0, y0, x, y);

            if (area1 < 0 && area2 < 0 && area3 < 0)
                yarl_draw_point(yarl, x, y, color);

        }
    }

}

YarlColor yarl_lerp_color(YarlColor a, YarlColor b, float t) {

    uint8_t rr = YARL_LERP(YARL_COLOR_R(a), YARL_COLOR_R(b), t);
    uint8_t rg = YARL_LERP(YARL_COLOR_G(a), YARL_COLOR_G(b), t);
    uint8_t rb = YARL_LERP(YARL_COLOR_B(a), YARL_COLOR_B(b), t);
    uint8_t ra = YARL_LERP(YARL_COLOR_A(a), YARL_COLOR_A(b), t);

    YarlColor out =
        (rr << 3*8) |
        (rg << 2*8) |
        (rb << 1*8) |
        ra;

    return out;

}
