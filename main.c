#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <sys/param.h>


#include "yarl.h"
#include "backend.h"



int main(void) {

    Yarl yarl = yarl_init(500, 500);

    yarl_clear(yarl, 0x696969ff);

    yarl_draw_rect(
        yarl,
        yarl_get_width(yarl)/4,
        yarl_get_height(yarl)/4,
        yarl_get_width(yarl)/2,
        yarl_get_height(yarl)/2,
        0x00ffffff
    );

    yarl_draw_circle(yarl, yarl_get_width(yarl)/2, yarl_get_height(yarl)/2, 50, 0x00ff0000);

    yarl_draw_line(
        yarl,
        yarl_get_width(yarl)/2,
        yarl_get_height(yarl)/2,
        yarl_get_width(yarl),
        yarl_get_height(yarl),
        YARL_RED
    );
    yarl_draw_line(
        yarl,
        yarl_get_width(yarl)/2,
        yarl_get_height(yarl)/2,
        yarl_get_width(yarl),
        0,
        YARL_BLUE
    );

    yarl_draw_line(
        yarl,
        yarl_get_width(yarl)/2,
        yarl_get_height(yarl)/2,
        0,
        0,
        YARL_GREEN
    );

    // yarl_draw_line(
    //     yarl,
    //     yarl_get_canvas_width(yarl)/2,
    //     yarl_get_canvas_height(yarl)/2,
    //     0,
    //     // TODO: investigate
    //     yarl_get_canvas_height(yarl),
    //     PINK
    // );

    render_ppm(yarl, "output.ppm");

    yarl_destroy(yarl);


    return 0;
}
