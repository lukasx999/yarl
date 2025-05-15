#include <assert.h>
#include <linux/limits.h>
#include <sys/stat.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image_write.h"

#include <yarl.h>
#include "examples.c"

#define DIRNAME "gallery"
#define CANVAS_HEIGHT 500
#define CANVAS_WIDTH 500

int main(void) {

    Yarl yarl = yarl_init(CANVAS_WIDTH, CANVAS_HEIGHT);
    assert(yarl != NULL);

    for (size_t i=0; i < examples_size; ++i) {
        examples[i].fn(yarl);
        char buf[PATH_MAX] = { 0 };
        mkdir(DIRNAME, 0777);
        snprintf(buf, sizeof(buf), DIRNAME "/%s.png", examples[i].name);

        YarlColor data[CANVAS_HEIGHT][CANVAS_WIDTH] = { 0 };
        for (int y=0; y < CANVAS_HEIGHT; ++y) {
            YarlColor **color = yarl_get_canvas(yarl);
            memcpy(data[y], color[y], sizeof(YarlColor)*CANVAS_WIDTH);
        }

        int ret = stbi_write_png(buf, CANVAS_WIDTH, CANVAS_HEIGHT, 4, data, 4 * CANVAS_WIDTH);
        assert(ret != 0);

    }

    yarl_destroy(yarl);
    return 0;
}
