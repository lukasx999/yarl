#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "./yarl/yarl.h"

int main(void)
{

    Yarl *yarl = yarl_init(500, 500, YARL_COLOR_FORMAT_RGB);
    assert(yarl != NULL);
    int w = yarl_get_width(yarl);
    int h = yarl_get_height(yarl);
    yarl_fill(yarl, YARL_GREY);
    yarl_draw_triangle(yarl, w/2, 0, w, h, 0, h, YARL_RED);
    // yarl_draw_triangle(yarl, w/2, 0, 0, h, w, h, YARL_BLUE);

    FILE *f = fopen("output.ppm", "wb");
    if (f == NULL)
        return -1;

    int stride = 3;
    fprintf(f, "P6 %d %d %d\n", w, h, 255);
    fwrite(yarl_get_buffer(yarl), 1, w * h * stride, f);

    return 0;
}
