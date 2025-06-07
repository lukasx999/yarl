#include <assert.h>
#include <linux/limits.h>
#include <sys/stat.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <yarl.h>
#include "examples.c"

#define DIRNAME "gallery"

int main(void) {

    unsigned char *buffer = malloc(500 * 500 * 4);
    Yarl *yarl = yarl_init(buffer, 500, 500, YARL_COLOR_FORMAT_RGBA);
    int w = yarl_get_width(yarl);
    int h = yarl_get_height(yarl);
    int stride = 4;
    assert(yarl != NULL);

    for (size_t i=0; i < examples_size; ++i) {
        examples[i].fn(yarl);
        char path_buf[PATH_MAX] = { 0 };
        mkdir(DIRNAME, 0777);
        snprintf(path_buf, sizeof(path_buf), DIRNAME "/%s.png", examples[i].name);

        unsigned char *buffer = yarl_get_buffer(yarl);
        int ret = stbi_write_png(path_buf, w, h, stride, buffer, stride * w);
        assert(ret != 0);
    }

    free(buffer);
    return 0;
}
