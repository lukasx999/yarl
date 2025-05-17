#include <stdlib.h>
#include <assert.h>

#include "./yarl/yarl.h"

int main(void)
{

    Yarl *yarl = yarl_init(500, 500, YARL_COLOR_FORMAT_RGBA);
    assert(yarl != NULL);
    yarl_draw_rect(yarl, 50, 50, 100, 100, YARL_BLUE);

    yarl_render_ppm(yarl, "output.ppm");

    return 0;
}
