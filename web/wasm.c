#include "../yarl/yarl.h"
#include <stdio.h>

unsigned char *render(unsigned char *buffer, int width, int height) {
    // printf("hello, wasm\n");
    Yarl *yarl = yarl_init(width, height, YARL_COLOR_FORMAT_RGBA);

    yarl_fill(yarl, YARL_BLUE);
    yarl_draw_rect(yarl, 100, 100, 300, 300, YARL_BLACK);

    return yarl_get_buffer(yarl);
}
