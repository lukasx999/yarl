#include "yarl.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>



// create a color struct from the given binary buffer, obeying the given `format`
static YarlColor color_from_buffer(unsigned char *buffer, YarlColorFormat format) {
    switch (format) {
        case YARL_COLOR_FORMAT_ARGB: return (YarlColor) {
            .a = buffer[0],
            .r = buffer[1],
            .g = buffer[2],
            .b = buffer[3],
        };
        case YARL_COLOR_FORMAT_ABGR: return (YarlColor) {
            .a = buffer[0],
            .r = buffer[3],
            .g = buffer[2],
            .b = buffer[1],
        };
        case YARL_COLOR_FORMAT_RGBA: return (YarlColor) {
            .r = buffer[0],
            .g = buffer[1],
            .b = buffer[2],
            .a = buffer[3],
        };
        case YARL_COLOR_FORMAT_BGRA: return (YarlColor) {
            .r = buffer[2],
            .g = buffer[1],
            .b = buffer[0],
            .a = buffer[3],
        };
        case YARL_COLOR_FORMAT_RGB: return (YarlColor) {
            .r = buffer[0],
            .g = buffer[1],
            .b = buffer[2],
        };
        case YARL_COLOR_FORMAT_BGR: return (YarlColor) {
            .r = buffer[2],
            .g = buffer[1],
            .b = buffer[0],
        };
    }
}

// Writes `color` into `buffer`, obeying the given `format`
static void color_to_buffer(unsigned char *buffer, YarlColor color, YarlColorFormat format) {
    switch (format) {
        case YARL_COLOR_FORMAT_ARGB:
            buffer[0] = color.a;
            buffer[1] = color.r;
            buffer[2] = color.g;
            buffer[3] = color.b;
            break;
        case YARL_COLOR_FORMAT_ABGR:
            buffer[0] = color.a;
            buffer[3] = color.r;
            buffer[2] = color.g;
            buffer[1] = color.b;
            break;
        case YARL_COLOR_FORMAT_RGBA:
            buffer[0] = color.r;
            buffer[1] = color.g;
            buffer[2] = color.b;
            buffer[3] = color.a;
            break;
        case YARL_COLOR_FORMAT_BGRA:
            buffer[2] = color.r;
            buffer[1] = color.g;
            buffer[0] = color.b;
            buffer[3] = color.a;
            break;
        case YARL_COLOR_FORMAT_RGB:
            buffer[0] = color.r;
            buffer[1] = color.g;
            buffer[2] = color.b;
            break;
        case YARL_COLOR_FORMAT_BGR:
            buffer[2] = color.r;
            buffer[1] = color.g;
            buffer[0] = color.b;
            break;
    }
}


void yarl_init(
    Yarl *yarl,
    unsigned char *buffer,
    int width,
    int height,
    YarlColorFormat format,
    YarlEnvironment env
) {

    yarl->height = height;
    yarl->width  = width;
    yarl->buffer = buffer;
    yarl->format = format;
    yarl->env    = env;
}

static unsigned char *buffer_offset(const Yarl *yarl, int x, int y) {
    size_t offset = y * yarl->width + x;
    return yarl->buffer + offset * yarl_get_format_stride(yarl->format);
}

YarlColor yarl_get_pixel(const Yarl *yarl, int x, int y) {
    // if (x >= yarl->width && x < 0)
    //     yarl->env.panic();
    //
    // if (y >= yarl->height && y < 0)
    //     yarl->env.panic();

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
    }
}

void yarl_draw_pixel(Yarl *yarl, int x, int y, YarlColor color) {

    // if (x >= yarl->width)
    //     yarl->env.panic();
    //
    // if (y >= yarl->height)
    //     yarl->env.panic();

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
    YarlEnvironment env = yarl->env;

    start_angle = env.fmodf(start_angle, 360);

    if (start_angle < 0.)
        start_angle = 360. - env.fabsf(start_angle);

    for (float a=start_angle; a < start_angle + rot_count; ++a) {
        int x = cx + r * env.cos(YARL_DEG_TO_RAD(a));
        int y = cy + r * env.sin(YARL_DEG_TO_RAD(a));
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
static float rotation_angle_around_center(YarlEnvironment env, int x, int y) {
    float angle = env.floorf(YARL_RAD_TO_DEG(env.atanf((float) y / x)));
    if (y > 0.)
        angle = 360. - angle;

    if (x < 0.)
        angle = 180. - angle;

    angle = env.fabsf(angle);
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
    YarlEnvironment env = yarl->env;

    start_angle = env.fmodf(start_angle, 360.);

    if (start_angle < 0.)
        start_angle = 360. - env.fabsf(start_angle);

    int x0 = YARL_CLAMP(cx - r, 0, yarl->width);
    int y0 = YARL_CLAMP(cy - r, 0, yarl->height);
    int x1 = YARL_CLAMP(cx + r, 0, yarl->width);
    int y1 = YARL_CLAMP(cy + r, 0, yarl->height);

    for (int x=x0; x < x1; ++x) {
        for (int y=y0; y < y1; ++y) {

            // position relative to arc middle
            int mx = x - cx;
            int my = cy - y;

            float angle = rotation_angle_around_center(env, mx, my);

            for (float a=start_angle; a < start_angle + rot_count; ++a) {

                // coordinates of arc outline
                int xo = r * env.cos(YARL_DEG_TO_RAD(a));
                int yo = r * env.sin(YARL_DEG_TO_RAD(a));

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

            double dist = (cx-x) * (cx-x) + (cy-y) * (cy-y);

            if (dist < r*r)
                yarl_draw_pixel(yarl, x, y, color);
        }
    }

}

void yarl_draw_ellipse(Yarl *yarl, int cx, int cy, int rx, int ry, YarlColor color) {

    int x0 = YARL_CLAMP(cx - rx, 0, yarl->width);
    int y0 = YARL_CLAMP(cy - ry, 0, yarl->height);
    int x1 = YARL_CLAMP(cx + rx, 0, yarl->width);
    int y1 = YARL_CLAMP(cy + ry, 0, yarl->height);

    for (int y=y0; y < y1; ++y) {
        for (int x=x0; x < x1; ++x) {

            double dist = (cx-x) * (cx-x) + (cy-y) * (cy-y);

            // TODO:
            int r = rx+ry;

            if (dist < r*r)
                yarl_draw_pixel(yarl, x, y, color);
        }
    }

}

void yarl_draw_line(Yarl *yarl, int x0, int y0, int x1, int y1, YarlColor color) {
    yarl_draw_line_thick(yarl, x0, y0, x1, y1, color, 1);
}

void yarl_draw_line_thick(Yarl *yarl, int x0, int y0, int x1, int y1, YarlColor color, int thickness) {
    YarlEnvironment env = yarl->env;

    float dy = y1 - y0;
    float dx = x1 - x0;

    // avoid divide-by-zero errors
    if (dx == 0) {
        for (float y=y0; y < y1; ++y)
            yarl_draw_circle(yarl, x0, y, thickness, color);
        return;
    }

    float m = dy / dx;
    // the needed precision for rendering lines
    float step = env.fabsf(dx / yarl->width);
    int start = YARL_MIN(x0, x1);

    for (float x=start; x < start + env.fabsf(dx); x += step) {
        float y = m * (x - x0) + y0;
        yarl_draw_circle(yarl, x, y, thickness, color);
    }

}

static inline float triangle_edge_function(int x0, int y0, int x1, int y1, int x2, int y2) {
    return (x1-x0) * (y2-y0) - (y1-y0) * (x2-x0);
}

void yarl_draw_triangle(Yarl *yarl, int x0, int y0, int x1, int y1, int x2, int y2, YarlColor color) {

    // bounding box of triangle
    int xs = YARL_MIN3(x0, x1, x2);
    int xe = YARL_MAX3(x0, x1, x2);
    int ys = YARL_MIN3(y0, y1, y2);
    int ye = YARL_MAX3(y0, y1, y2);

    for (int y=ys; y < ye; ++y) {
        for (int x=xs; x < xe; ++x) {

            float area1 = triangle_edge_function(x0, y0, x1, y1, x, y);
            float area2 = triangle_edge_function(x1, y1, x2, y2, x, y);
            float area3 = triangle_edge_function(x2, y2, x0, y0, x, y);

            if ((area1 < 0 && area2 < 0 && area3 < 0) || (area1 > 0 && area2 > 0 && area3 > 0))
                yarl_draw_pixel(yarl, x, y, color);

        }
    }

}

void yarl_draw_text(Yarl *yarl, int x, int y, const char *text) {
    // TODO:
}

YarlColor yarl_lerp_color(YarlColor a, YarlColor b, float t) {
    return (YarlColor) {
        YARL_LERP(a.r, b.r, t),
        YARL_LERP(a.g, b.g, t),
        YARL_LERP(a.b, b.b, t),
        YARL_LERP(a.a, b.a, t),
    };
}
