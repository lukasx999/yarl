#include "yarl.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <sys/param.h>

#include "formats.h"



struct Yarl {
    int width, height;
    // binary canvas - could represent any color format
    // use the associated functions from `formats.h` for extracting color values
    unsigned char *buffer;
    YarlColorFormat format;
};

Yarl *yarl_init_buffer(unsigned char *buffer, int width, int height, YarlColorFormat format) {

    Yarl *yarl = malloc(sizeof(Yarl));
    if (yarl == NULL)
        return NULL;

    yarl->height = height;
    yarl->width  = width;
    yarl->buffer = buffer;
    yarl->format = format;

    return yarl;
}

Yarl *yarl_init(int width, int height, YarlColorFormat format) {

    size_t size = width * height;
    unsigned char *buffer = malloc(size * yarl_get_format_stride(format));
    if (buffer == NULL)
        return NULL;

    memset(buffer, 0x0, size);

    return yarl_init_buffer(buffer, width, height, format);
}

static unsigned char *buffer_offset(const Yarl *yarl, int x, int y) {
    size_t offset = y * yarl->width + x;
    return yarl->buffer + offset * yarl_get_format_stride(yarl->format);
}

YarlColor yarl_get_pixel(const Yarl *yarl, int x, int y) {
    assert(x < yarl->width && x >= 0);
    assert(y < yarl->height && y >= 0);
    return color_from_buffer(buffer_offset(yarl, x, y), yarl->format);
}

unsigned char *yarl_get_buffer(const Yarl *yarl) {
    return yarl->buffer;
}

int yarl_get_width(const Yarl *yarl) {
    return yarl->width;
}

int yarl_get_height(const Yarl *yarl) {
    return yarl->height;
}

YarlColorFormat yarl_get_format(const Yarl *yarl) {
    return yarl->format;
}

int yarl_get_format_stride(YarlColorFormat format) {
    switch (format) {
        case YARL_COLOR_FORMAT_ARGB:
        case YARL_COLOR_FORMAT_ABGR:
        case YARL_COLOR_FORMAT_RGBA:
        case YARL_COLOR_FORMAT_BGRA:
            return 4;
        case YARL_COLOR_FORMAT_RGB:
        case YARL_COLOR_FORMAT_BGR:
            return 3;
        default:
            assert(!"unknown color format");
    }
}

void yarl_destroy(Yarl *yarl) {
    free(yarl->buffer);
}

void yarl_draw_pixel(Yarl *yarl, int x, int y, YarlColor color) {
    color_to_buffer(buffer_offset(yarl, x, y), color, yarl->format);
}

void yarl_fill(Yarl *yarl, YarlColor color) {
    yarl_draw_rect(yarl, 0, 0, yarl->width, yarl->height, color);
}

void yarl_draw_rect_outline(Yarl *yarl, int x, int y, int w, int h, YarlColor color) {

    for (int i=y; i < y+h; ++i) {
        if (i == y || i == y+h-1) {
            for (int j=x; j < x+w; ++j)
                yarl_draw_pixel(yarl, j, i, color);
        } else {
            yarl_draw_pixel(yarl, x, i, color);
            yarl_draw_pixel(yarl, x+w, i, color);
        }
    }

}

void yarl_draw_rect(Yarl *yarl, int x0, int y0, int w, int h, YarlColor color) {
    for (int y=y0; y < y0+h; ++y)
        for (int x=x0; x < x0+w; ++x)
            yarl_draw_pixel(yarl, x, y, color);
}

void yarl_draw_arc_outline(Yarl *yarl, int cx, int cy, int r, float start_angle, float rot_count, YarlColor color) {

    start_angle = fmodf(start_angle, 360);

    if (start_angle < 0.)
        start_angle = 360. - fabsf(start_angle);

    for (float a=start_angle; a < start_angle + rot_count; ++a) {
        int x = cx + r * cos(YARL_DEG_TO_RAD(a));
        int y = cy + r * sin(YARL_DEG_TO_RAD(a));
        yarl_draw_pixel(yarl, x, y, color);
    }

}

// `````````````````````````````````````````
// ````````````````````270°`````````````````
// `````````````````````|```````````````````
// `````````225°````````|`````````315°``````
// `````````````````````|```````````````````
// `````````````````````|```````````````````
// ````180°<------------*------------>0°````
// `````````````````````|```````````````````
// `````````````````````|```````````````````
// `````````135°````````|`````````45°```````
// `````````````````````|```````````````````
// ````````````````````90°``````````````````
// ````````````````````````````````````````
// float rotation_angle_around_center(int x, int y) {
//     float angle = floorf(YARL_RAD_TO_DEG(atanf((float) y / x)));
//     if (y > 0.)
//         angle = 360. - angle;
//
//     if (x < 0.)
//         angle = 180. - angle;
//
//     angle = fabsf(angle);
//     return angle;
// }

static float rotation_angle_around_center(int x, int y) {
    float angle = floorf(YARL_RAD_TO_DEG(atanf((float) y / x)));
    if (y > 0.)
        angle = 360. - angle;

    if (x < 0.)
        angle = 180. - angle;

    angle = fabsf(angle);
    return angle;
}

void yarl_draw_arc(
    Yarl *yarl,
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
                    yarl_draw_pixel(yarl, x, y, color);

            }

        }
    }

}

void yarl_draw_circle_outline(Yarl *yarl, int cx, int cy, int r, YarlColor color) {
    yarl_draw_arc_outline(yarl, cx, cy, r, 0, 360, color);
}

void yarl_draw_circle(Yarl *yarl, int cx, int cy, int r, YarlColor color) {

    int x0 = YARL_CLAMP(cx - r, 0, yarl->width);
    int y0 = YARL_CLAMP(cy - r, 0, yarl->height);
    int x1 = YARL_CLAMP(cx + r, 0, yarl->width);
    int y1 = YARL_CLAMP(cy + r, 0, yarl->height);

    for (int y=y0; y < y1; ++y) {
        for (int x=x0; x < x1; ++x) {

            double dist = (cx - x) * (cx - x) + (cy - y) * (cy - y);

            if (dist < r*r)
                yarl_draw_pixel(yarl, x, y, color);
        }
    }

}

// TODO:
void yarl_draw_ellipse(Yarl *yarl, int cx, int cy, int rx, int ry, YarlColor color) {
    (void) cx;
    (void) cy;
    (void) rx;
    (void) ry;
    (void) color;
    (void) yarl;
    assert(!"TODO");
}

void yarl_draw_line(Yarl *yarl, int x0, int y0, int x1, int y1, YarlColor color) {
    yarl_draw_line_thick(yarl, x0, y0, x1, y1, color, 1);
}

void yarl_draw_line_thick(Yarl *yarl, int x0, int y0, int x1, int y1, YarlColor color, int thickness) {

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

void yarl_draw_triangle(Yarl *yarl, int x0, int y0, int x1, int y1, int x2, int y2, YarlColor color) {

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
                yarl_draw_pixel(yarl, x, y, color);

        }
    }

}

YarlColor yarl_lerp_color(YarlColor a, YarlColor b, float t) {
    return (YarlColor) {
        YARL_LERP(a.r, b.r, t),
        YARL_LERP(a.g, b.g, t),
        YARL_LERP(a.b, b.b, t),
        YARL_LERP(a.a, b.a, t),
    };
}
