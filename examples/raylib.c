#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include <raylib.h>

#include <yarl.h>
#include <backend/raylib.h>

#include "examples.c"

int main(void) {

    Yarl yarl = yarl_init(500, 500);

    SetTraceLogLevel(LOG_ERROR);
    InitWindow(500, 500, "yarl");
    SetTargetFPS(60);

    size_t i = 0;

    double time = 0.;

    while (!WindowShouldClose()) {
        BeginDrawing();

        examples[i].fn(yarl);

        if (GetTime() > time) {
            ++i;
            if (i >= examples_size)
                i = 0;
            time = GetTime() + 1;
        }

        yarl_render_raylib(yarl, 0, 0, 1);


        EndDrawing();
    }

    CloseWindow();

    yarl_destroy(yarl);

}
