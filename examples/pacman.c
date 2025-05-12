#include <stdio.h>
#include <math.h>

#include <raylib.h>

#include <yarl.h>
#include <backend/raylib.h>

int main(void) {

    SetTraceLogLevel(LOG_ERROR);
    InitWindow(500, 500, "yarl");
    SetTargetFPS(60);

    Yarl yarl = yarl_init(500, 500);
    int h = yarl_get_height(yarl);
    int w = yarl_get_width(yarl);

    float i = 25.;
    bool up = true;

    while (!WindowShouldClose()) {
        BeginDrawing();

        yarl_fill(yarl, YARL_GREY);

        float step = 5.;
        if (i < 25.) up = true;
        if (i > 35.) up = false;
        if (up) i+=step;
        else i-=step;

        yarl_draw_arc(yarl, w/2, h/2, 150, i, 360. - 2. * i, YARL_YELLOW);
        yarl_render_raylib(yarl, 0, 0, 1);

        EndDrawing();
    }

    CloseWindow();

    yarl_destroy(yarl);
}
