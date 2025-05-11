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
    yarl_draw_arc(yarl, w/2, h/2, 150, 45, -45, YARL_YELLOW);
    // FIXME:
    // yarl_draw_arc(yarl, w/2, h/2, 150, -45, 45, YARL_BLUE);
    // FIXME:
    // yarl_draw_arc(yarl, w/2, h/2, 150, 180, 45, YARL_RED);

    yarl_render_ppm(yarl, "output.ppm");
}

int main(void) {

    Yarl yarl = yarl_init(500, 500);
    draw(yarl);

    yarl_destroy(yarl);

    return 0;
}
