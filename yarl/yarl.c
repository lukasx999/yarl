#include "yarl.h"

#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <sys/param.h>



struct YarlContext {
    int width, height;
    YarlColor **canvas;
};

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
    // TODO: bounds checking
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

// angle is in degrees
void yarl_draw_arc_outline(Yarl yarl, int cx, int cy, int r, int start_angle, int end_angle, YarlColor color) {

    // normalize angles
    start_angle = start_angle % 360;
    end_angle   = end_angle   % 360;

    if (end_angle < start_angle)
        end_angle += 360;

    for (int a=start_angle; a < end_angle; ++a) {
        int x = cx + r * cos(YARL_DEG_TO_RAD(a));
        int y = cy + r * sin(YARL_DEG_TO_RAD(a));
        yarl_draw_point(yarl, x, y, color);
    }

}

void yarl_draw_arc(Yarl yarl, int cx, int cy, int r, int start_angle, int end_angle, YarlColor color) {

    // normalize angles
    start_angle = start_angle % 360;
    end_angle   = end_angle   % 360;

    if (end_angle < start_angle)
        end_angle += 360;

    int x0 = YARL_CLAMP(cx - r, 0, yarl->width);
    int y0 = YARL_CLAMP(cy - r, 0, yarl->height);
    int x1 = YARL_CLAMP(cx + r, 0, yarl->width);
    int y1 = YARL_CLAMP(cy + r, 0, yarl->height);

    printf("end: %d\n", end_angle);

    for (int x=x0; x < x1; ++x) {
    for (int y=y0; y < y1; ++y) {
    // int x = 400, y = 100;
    //     {
    //      {

            // yarl_draw_circle(yarl, cx, cy, 5, YARL_BLUE);
            // yarl_draw_circle(yarl, x, y, 5, YARL_RED);

            // position relative to arc middle
            int mx = x - cx;
            int my = cy - y;

            float angle = floorf(YARL_RAD_TO_DEG(atanf((float) my / mx)));
            if (my > 0)
                angle = 360 - angle;

            if (mx < 0)
                angle = 180 - angle;

            angle = fabsf(angle);

            printf("%f\n", angle);


            for (int a=start_angle; a < end_angle; ++a) {

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



// TODO: use M_PI

// angle is in degrees
// void yarl_draw_arc(Yarl yarl, int cx, int cy, int r, int start_angle, int end_angle, YarlColor color) {
//
//     // normalize angles
//     start_angle = start_angle % 360;
//     end_angle   = end_angle   % 360;
//
//     if (end_angle < start_angle)
//         end_angle += 360;
//
//     int x0 = YARL_CLAMP(cx - r, 0, yarl->width);
//     int y0 = YARL_CLAMP(cy - r, 0, yarl->height);
//     int x1 = YARL_CLAMP(cx + r, 0, yarl->width);
//     int y1 = YARL_CLAMP(cy + r, 0, yarl->height);
//
//     // for (int x=x0; x < x1; ++x) {
//     // for (int y=y0; y < y1; ++y) {
//     int x = 100, y = 100;
//     {
//         {
//
//             yarl_draw_circle(yarl, cx, cy, 5, YARL_BLUE);
//             yarl_draw_circle(yarl, x, y, 5, YARL_RED);
//
//             // position relative to arc middle
//             int mx = x - cx;
//             int my = cy - y;
//             // my = -my;
//
//             float lenm = sqrt(mx*mx + my*my);
//
//             float bx = x1 - cx;
//             float by = 0;
//             float lenb = sqrt(bx*bx + by*by);
//
//             float dotmb = mx*my + bx*by;
//
//             float angle = floorf(YARL_RAD_TO_DEG(acosf(dotmb / (lenm*lenb))));
//
//             if (mx < 0)
//                 angle = 180 - angle;
//
//             printf("angle: %f\n", angle);
//
//             for (int a=start_angle; a < end_angle; ++a) {
//
//                 // coordinates of arc outline
//                 int xo = r * cos(YARL_DEG_TO_RAD(a));
//                 int yo = r * sin(YARL_DEG_TO_RAD(a));
//
//                 int leno = xo*xo + yo*yo;
//                 int len  = mx*mx + my*my;
//
//                 if (angle == a && len < leno)
//                     yarl_draw_point(yarl, x, y, color);
//             }
//
//         }
//     }
//
// }

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

// TODO:
void yarl_draw_triangle(Yarl yarl, int x0, int y0, int x1, int y1, YarlColor color) {
    assert(!"TODO");
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
