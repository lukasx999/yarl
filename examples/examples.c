#include <stddef.h>
#include <stdint.h>
#include <math.h>

#include <yarl.h>


void triangles(Yarl yarl) {

    int w = yarl_get_width(yarl);
    int h = yarl_get_height(yarl);

    yarl_fill(yarl, YARL_GREY);
    yarl_draw_triangle(yarl, w/2, 25, 0, h, w, h, YARL_DARK_BLUE);
    yarl_draw_triangle(yarl, w/2, 50, 50, h-50, w-50, h-50, YARL_BLUE);

    yarl_draw_rect(yarl, 0, 0, 50, h, YARL_DARK_RED);
    yarl_draw_triangle(yarl, 50, 0, 0, h, w, h, YARL_DARK_RED);
    yarl_draw_triangle(yarl, 0, 0, 0, h, w, h, YARL_RED);

    yarl_draw_rect(yarl, w-50, 0, 50, h, YARL_DARK_GREEN);
    yarl_draw_triangle(yarl, w-50, 0, 0, h, w, h, YARL_DARK_GREEN);
    yarl_draw_triangle(yarl, w, 0, 0, h, w, h, YARL_GREEN);


    yarl_draw_triangle(yarl, w/2, h/2-250, -25, h, w+25, h, YARL_DARK_PURPLE);
    yarl_draw_triangle(yarl, w/2, h/2-200, 0, h, w, h, YARL_PURPLE);

    yarl_draw_triangle(yarl, w/2, h/2-50, 25, h, w-25, h, YARL_DARK_YELLOW);
    yarl_draw_triangle(yarl, w/2, h/2, 50, h, w-50, h, YARL_YELLOW);
}

void pacman(Yarl yarl) {

    yarl_fill(yarl, YARL_BLACK);
    yarl_draw_arc(
        yarl,
        yarl_get_width(yarl)  / 2,
        yarl_get_height(yarl) / 2,
        150,
        35,
        -35,
        YARL_YELLOW
    );

}

void gradient(Yarl yarl) {

    int w = yarl_get_width(yarl);
    int h = yarl_get_height(yarl);

    yarl_fill(yarl, YARL_BLACK);

    for (int i=0; i < w; ++i) {
        int range = ceil(w / 255.);
        YarlColor color = yarl_lerp_color(YARL_BLACK, YARL_RED, i/range+1);
        yarl_draw_rect(yarl, i, 0, 1, h, color);
    }

}

void grid(Yarl yarl) {

    int h = yarl_get_height(yarl);
    int w = yarl_get_width(yarl);

    yarl_fill(yarl, YARL_BLACK);

    int size = 50;
    int spacing = 1;

    YarlColor color = YARL_BLUE;

    for (int y=0; y < h/(size+spacing); ++y) {
        for (int x=0; x < w/(size+spacing); ++x) {
            yarl_draw_rect(
                yarl,
                spacing + x * (size+spacing),
                spacing + y * (size+spacing),
                size,
                size,
                color
            );
        }
    }

}

void rectangles(Yarl yarl) {

    int w = yarl_get_width(yarl);
    int h = yarl_get_height(yarl);

    yarl_fill(yarl, YARL_BLACK);
    yarl_draw_rect(yarl, w/4, h/4, w/2, h/2, YARL_BLUE);

    yarl_draw_rect(yarl, w/8, h/8, w/4, h/4, YARL_RED);
    yarl_draw_rect(yarl, w/8, h - 3*(h/8), w/4, 2*(h/8), YARL_RED);
    yarl_draw_rect(yarl, w - 3*(w/8), h/8, w/4, h/4, YARL_RED);
    yarl_draw_rect(yarl, w - 3*(w/8), h - 3*(h/8), w/4, 2*(h/8), YARL_RED);

}

void japan(Yarl yarl) {
    int w = yarl_get_width(yarl);
    int h = yarl_get_height(yarl);
    yarl_fill(yarl, YARL_WHITE);
    yarl_draw_circle(yarl, w/2, h/2, 100, YARL_RED);
}

void circle_gradient(Yarl yarl) {

    int w = yarl_get_width(yarl);
    int h = yarl_get_height(yarl);
    yarl_fill(yarl, YARL_BLACK);

    for (int i=w/2; i > 0; --i) {
        YarlColor color = yarl_lerp_color(YARL_RED, YARL_BLUE, i);
        yarl_draw_circle(yarl, w/2, h/2, i, color);
    }

}



typedef struct {
    void (*fn)(Yarl);
    const char *name;
} Example;

#define EXAMPLE(func) \
    { .fn = func, .name = #func }

Example examples[] = {
    EXAMPLE(circle_gradient),
    EXAMPLE(pacman),
    EXAMPLE(gradient),
    EXAMPLE(grid),
    EXAMPLE(rectangles),
    EXAMPLE(japan),
    EXAMPLE(triangles),
};

size_t examples_size = sizeof(examples) / sizeof(*examples);
