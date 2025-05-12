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

    float i = 0;
    bool up = true;

    while (!WindowShouldClose()) {
        BeginDrawing();

        yarl_fill(yarl, YARL_GREY);

        float angle = floorf(YARL_LERP(25, 35, i));

        if (i < -1.) up = true;
        if (i > 1.) up = false;
        if (up) i++;
        else i--;

        yarl_draw_arc(yarl, w/2, h/2, 150, angle, 360. - 2. * angle, YARL_YELLOW);
        yarl_render_raylib(yarl, 0, 0, 1);

        EndDrawing();
    }

    CloseWindow();

    yarl_destroy(yarl);
}
