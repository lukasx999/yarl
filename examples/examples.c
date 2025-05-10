#include <assert.h>
#include <stdio.h>
#include <math.h>

#include "../yarl/yarl.h"

#define CANVAS_WIDTH 500
#define CANVAS_HEIGHT 500

void pacman(Yarl yarl) {

    yarl_clear(yarl, YARL_BLACK);
    yarl_draw_arc(
        yarl,
        yarl_get_width(yarl)  / 2,
        yarl_get_height(yarl) / 2,
        50,
        35,
        -35,
        YARL_YELLOW
    );

    int ret = render_ppm(yarl, "pacman.ppm");
    assert(ret == 0);

}

void gradient(Yarl yarl) {

    int w = yarl_get_width(yarl);
    int h = yarl_get_height(yarl);

    yarl_clear(yarl, YARL_BLACK);

    for (int i=0; i < w; ++i) {
        int range = ceil(w / 255.);
        YarlColor color = yarl_lerp_color(YARL_BLACK, YARL_RED, i/range);
        yarl_draw_rect(yarl, i, 0, 1, h, color);
    }

    render_ppm(yarl, "gradient.ppm");

}

void grid(Yarl yarl) {

    int w = yarl_get_width(yarl);
    int h = yarl_get_height(yarl);

    yarl_clear(yarl, YARL_BLACK);

    int size = 5;
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

    render_ppm(yarl, "grid.ppm");
}

void rectangles(Yarl yarl) {

    int w = yarl_get_width(yarl);
    int h = yarl_get_height(yarl);

    yarl_clear(yarl, YARL_BLACK);
    yarl_draw_rect(yarl, w/4, h/4, w/2, h/2, YARL_BLUE);

    yarl_draw_rect(yarl, w/8, h/8, w/4, h/4, YARL_RED);
    yarl_draw_rect(yarl, w/8, h - 3*(h/8), w/4, 2*(h/8), YARL_RED);
    yarl_draw_rect(yarl, w - 3*(w/8), h/8, w/4, h/4, YARL_RED);
    yarl_draw_rect(yarl, w - 3*(w/8), h - 3*(h/8), w/4, 2*(h/8), YARL_RED);

    render_ppm(yarl, "rectangles.ppm");
}

int main(void) {

    Yarl yarl = yarl_init(CANVAS_WIDTH, CANVAS_HEIGHT);

    pacman(yarl);
    rectangles(yarl);
    grid(yarl);
    gradient(yarl);

    yarl_destroy(yarl);

    return 0;
}
