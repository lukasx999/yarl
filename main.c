#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./yarl/yarl.h"

int main(void) {

    YarlEnvironment env = {
        .floorf = floorf,
        .fabsf  = fabsf,
        .fmodf  = fmodf,
        .atanf  = atanf,
        .sin    = sin,
        .cos    = cos,
        .panic  = abort,
    };

    Yarl yarl = { 0 };
    unsigned char buffer[500*500*3] = { 0 };
    yarl_init(&yarl, buffer, 500, 500, YARL_COLOR_FORMAT_RGB, env);

    yarl_fill(&yarl, YARL_BLUE);

    FILE *f = fopen("output.ppm", "wb");

    int w = yarl_get_width(&yarl);
    int h = yarl_get_height(&yarl);
    int stride = 3;
    fprintf(f, "P6 %d %d %d\n", w, h, 255);
    fwrite(yarl_get_buffer(&yarl), 1, w * h * stride, f);

    fclose(f);

    return 0;
}
