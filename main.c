#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include <yarl.h>
#include <backend/ppm.h>



void draw(Yarl yarl) {

    int h = yarl_get_height(yarl);
    int w = yarl_get_width(yarl);

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

    yarl_render_ppm(yarl, "output.ppm");
}

int main(void) {

    Yarl yarl = yarl_init(1000, 1000);
    draw(yarl);

    yarl_destroy(yarl);

    return 0;
}
