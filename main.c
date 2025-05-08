#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <sys/param.h>

#include <raylib.h>

#define YARL_COLORS
#include "yarl.h"

#define PIXEL_SIZE 1

static void render(Yarl yarl) {

    for (int y=0; y < yarl_get_height(yarl); ++y) {
        for (int x=0; x < yarl_get_width(yarl); ++x) {
            Color color = GetColor(yarl_get_canvas(yarl)[y][x]);
            DrawRectangle(
                x*PIXEL_SIZE,
                y*PIXEL_SIZE,
                PIXEL_SIZE,
                PIXEL_SIZE,
                color
            );
        }
    }
}

int main(void) {

    Yarl yarl = yarl_init(500, 500);

    InitWindow(1600, 900, "");

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
        RED
    );
    yarl_draw_line(
        yarl,
        yarl_get_width(yarl)/2,
        yarl_get_height(yarl)/2,
        yarl_get_width(yarl),
        0,
        BLUE
    );

    yarl_draw_line(
        yarl,
        yarl_get_width(yarl)/2,
        yarl_get_height(yarl)/2,
        0,
        0,
        GREEN
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


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        render(yarl);
        EndDrawing();
    }

    CloseWindow();

    yarl_destroy(yarl);


    return 0;
}
