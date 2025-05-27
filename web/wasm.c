#include "../yarl/yarl.h"
#include <stdio.h>

unsigned char *render(unsigned char *buffer, int width, int height) {
    // Yarl *yarl = yarl_init(width, height, YARL_COLOR_FORMAT_RGBA);
    Yarl *yarl = yarl_init_buffer(buffer, width, height, YARL_COLOR_FORMAT_RGBA);

    yarl_fill(yarl, YARL_BLUE);
    yarl_draw_rect(yarl, 100, 100, 200, 200, YARL_BLACK);

    return yarl_get_buffer(yarl);
}
