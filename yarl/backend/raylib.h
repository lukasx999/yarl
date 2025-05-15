#include <yarl.h>

#include <raylib.h>

static inline void yarl_render_raylib(const Yarl yarl, int x0, int y0, float scale) {
    for (int y=0; y < yarl_get_height(yarl); ++y) {
        for (int x=0; x < yarl_get_width(yarl); ++x) {
            Color color = GetColor(yarl_get_pixel(yarl, x, y));
            DrawRectangle(
                x0 + x * scale,
                y0 + y * scale,
                scale,
                scale,
                color
            );
        }
    }
}
