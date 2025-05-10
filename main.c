#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include <raylib.h>

#include "yarl/yarl.h"


void backend_raylib(Yarl yarl) {
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(1000, 1000, "yarl");
    while (!WindowShouldClose()) {
        BeginDrawing();
        yarl_render_raylib(yarl, 50, 50, 1);
        EndDrawing();
    }
    CloseWindow();
}


int main(void) {


    Yarl yarl = yarl_init(500, 500);

    int height = yarl_get_height(yarl);
    int width = yarl_get_width(yarl);

    yarl_fill(yarl, YARL_BLACK);

    printf("%d\n", YARL_COLOR_R(YARL_BLUE));

    backend_raylib(yarl);
    yarl_render_ppm(yarl, "output.ppm");

    yarl_destroy(yarl);


    return 0;
}
