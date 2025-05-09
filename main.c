#include <raylib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>


#include "yarl/yarl.h"
#include "yarl/backend.h"


void backend_raylib(Yarl yarl) {
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(1000, 1000, "yarl");
    while (!WindowShouldClose()) {
        BeginDrawing();
        render_raylib(yarl, 50, 50, 1);
        EndDrawing();
    }
    CloseWindow();
}


int main(void) {


    Yarl yarl = yarl_init(500, 500);

    int height = yarl_get_height(yarl);
    int width = yarl_get_width(yarl);

    yarl_clear(yarl, 0x696969ff);

    yarl_draw_rect(yarl, width/4, height/4, width/2, height/2, YARL_CYAN);
    yarl_draw_circle(yarl, width/2, height/2, 50, YARL_BLACK);
    yarl_draw_triangle_outline(yarl, 100, 100, width-100, height-100, 100, height-100, YARL_RED);

    // yarl_draw_line(yarl, width/2, height/2, width, height, YARL_RED);
    // yarl_draw_line(yarl, width/2, height/2, width, 0, YARL_BLUE);
    // yarl_draw_line(yarl, width/2, height/2, 0, 0, YARL_GREEN);
    // yarl_draw_line(yarl, width/2, height/2, 0, height, YARL_PINK);
    // yarl_draw_line(yarl, 0, height/2, width, height/2, YARL_YELLOW);
    // yarl_draw_line(yarl, width/2, 0, width/2, height, YARL_PURPLE);
    //
    // yarl_draw_line(yarl, 100, 100, width-100, height-100, YARL_RED);

    backend_raylib(yarl);
    render_ppm(yarl, "output.ppm");

    yarl_destroy(yarl);


    return 0;
}
