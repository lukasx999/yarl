#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include <X11/Xlib.h>

#define YARL_BACKEND_XLIB
#include <yarl.h>
#include <backend/xlib.h>



void draw(Yarl yarl) {

    int h = yarl_get_height(yarl);
    int w = yarl_get_width(yarl);
    int size = 100;

    yarl_fill(yarl, YARL_GREY);
    yarl_draw_rect(yarl, w/2-size, h/2-size, size, size, YARL_BLUE);
    yarl_draw_circle(yarl, w/2, h/2, 50, YARL_RED);
}


int main(void) {

    Yarl yarl = yarl_init(500, 500);
    draw(yarl);

    yarl_destroy(yarl);

    return 0;
}
