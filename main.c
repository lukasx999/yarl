#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <sys/param.h>

#include <raylib.h>

#define DEBUG

#define CANVAS_WIDTH 500
#define CANVAS_HEIGHT 500

#define PIXEL_SIZE 1

typedef uint32_t color_t;

static uint32_t canvas[CANVAS_HEIGHT][CANVAS_WIDTH] = { 0 };

void clear(color_t color) {
    for (int y=0; y < CANVAS_HEIGHT; ++y)
        for (int x=0; x < CANVAS_WIDTH; ++x)
            canvas[y][x] = color;
}

void rect(int x, int y, int w, int h, color_t color) {
    for (int i=y; i < y+h; ++i)
        for (int j=x; j < x+w; ++j)
            canvas[i][j] = color;
}

void circle(int cx, int cy, int radius, color_t color) {
    for (int y=cy-radius; y < cy+radius; ++y) {
        for (int x=cx-radius; x < cx+radius; ++x) {

            double dist = sqrt(
                (x - cx) * (x - cx) + (y - cy) * (y - cy)
            );

            if (dist < radius)
                canvas[y][x] = color;
        }
    }
}

void line(int ax, int ay, int bx, int by, color_t color) {

    int   sx = MIN(ax, bx);
    int   sy = MIN(ay, by);
    float dy = by - ay;
    float dx = bx - ax;
    float m  = dy / dx;

#ifdef DEBUG
    // rect(sx, sy, fabsf(dx), fabsf(dy), 0x808080ff);
#endif // DEBUG

    for (float x=0; x < fabsf(dx); ++x) {
        int diff = abs(ay - by);

        float y = m * x + diff;
        canvas[(size_t)fabsf(y)][sy+(size_t)x] = color;
    }

}

static void render(void) {

    for (size_t y=0; y < CANVAS_HEIGHT; ++y) {
        for (size_t x=0; x < CANVAS_WIDTH; ++x) {
            Color color = GetColor(canvas[y][x]);
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

    InitWindow(1600, 900, "");

    clear(0x696969ff);
    // rect(
    //     CANVAS_WIDTH/4,
    //     CANVAS_HEIGHT/4,
    //     CANVAS_WIDTH/2,
    //     CANVAS_HEIGHT/2,
    //     0x00ffffff
    // );
    // circle(CANVAS_WIDTH/2, CANVAS_HEIGHT/2, 50, 0x00ff0000);

    line(CANVAS_WIDTH/2, CANVAS_HEIGHT/2, CANVAS_WIDTH, CANVAS_HEIGHT, 0xff0000ff);
    line(CANVAS_WIDTH/2, CANVAS_HEIGHT/2, CANVAS_WIDTH, 0, 0x00ff00ff);
    line(CANVAS_WIDTH/2, CANVAS_HEIGHT/2, 0, 0, 0x0000ffff);
    line(CANVAS_WIDTH/2, CANVAS_HEIGHT/2, 0, CANVAS_HEIGHT, 0xff00ffff);

    while (!WindowShouldClose()) {
        BeginDrawing();
        render();
        EndDrawing();
    }

    CloseWindow();



    return 0;
}
