#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

#include <raylib.h>

#include <yarl.h>

#include "examples.c"

int main(void) {

    unsigned char *buffer = malloc(500 * 500 * 4);
    Yarl *yarl = yarl_init(buffer, 500, 500, YARL_COLOR_FORMAT_RGBA);
    assert(yarl != NULL);

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

        for (int y=0; y < yarl_get_height(yarl); ++y) {
            for (int x=0; x < yarl_get_width(yarl); ++x) {
                YarlColor color = yarl_get_pixel(yarl, x, y);
                Color rlcolor = { color.r, color.g, color.b, color.a };
                DrawRectangle(x, y, 1, 1, rlcolor);
            }
        }


        EndDrawing();
    }

    CloseWindow();
    free(buffer);

    return 0;
}
