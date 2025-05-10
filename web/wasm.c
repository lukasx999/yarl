#include "../yarl/yarl.h"

void render(void) {
    Yarl yarl = yarl_init(500, 500);

    yarl_fill(yarl, YARL_BLUE);
    yarl_draw_rect(yarl, 100, 100, 300, 300, YARL_BLACK);
}
