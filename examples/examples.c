#include <assert.h>

#include "../yarl/yarl.h"

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

void rectangles(Yarl yarl) {

    int w = yarl_get_width(yarl);
    int h = yarl_get_height(yarl);

    yarl_clear(yarl, YARL_BLACK);
    yarl_draw_rect(yarl, w/4, h/4, w/2, h/2, YARL_BLUE);

    render_ppm(yarl, "rectangles.ppm");
}

int main(void) {

    Yarl yarl = yarl_init(500, 500);

    pacman(yarl);
    rectangles(yarl);

    yarl_destroy(yarl);

    return 0;
}
