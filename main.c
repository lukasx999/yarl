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

    yarl_draw_triangle(yarl, 0, h, w, h, YARL_YELLOW);
    yarl_draw_triangle(yarl, 0, h, w/2, h/2, YARL_RED);
    yarl_draw_triangle(yarl, 0, h, w/4, h/4, YARL_BLUE);

    yarl_render_ppm(yarl, "output.ppm");
}

int main(void) {

    Yarl yarl = yarl_init(500, 500);
    draw(yarl);

    yarl_destroy(yarl);

    return 0;
}
