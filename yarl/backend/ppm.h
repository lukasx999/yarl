#include <stdio.h>
#include <stdlib.h>

#include <yarl.h>

static inline int yarl_render_ppm(const Yarl yarl, const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (f == NULL)
        return -1;

    int w = yarl_get_width(yarl);
    int h = yarl_get_height(yarl);
    fprintf(f, "P6 %d %d %d\n", w, h, 255);

    for (int y=0; y < h; ++y) {
        for (int x=0; x < w; ++x) {
            YarlColor color = yarl_get_pixel(yarl, x, y);
            fwrite(&color, 3, 1, f);
        }
    }

    fclose(f);
    return 0;
}
