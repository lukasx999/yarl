#include <assert.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/limits.h>
#include <sys/stat.h>

#include <yarl.h>

#include "examples.c"

#define DIRNAME "gallery"

int main(void) {

    unsigned char *buffer = malloc(500 * 500 * 4);
    Yarl *yarl = yarl_init(buffer, 500, 500, YARL_COLOR_FORMAT_RGB);
    assert(yarl != NULL);

    for (size_t i=0; i < examples_size; ++i) {
        examples[i].fn(yarl);
        char path_buf[PATH_MAX] = { 0 };
        mkdir(DIRNAME, 0777);
        snprintf(path_buf, sizeof(path_buf), DIRNAME "/%s.ppm", examples[i].name);

        FILE *f = fopen(path_buf, "wb");
        if (f == NULL)
            return -1;

        int w = yarl_get_width(yarl);
        int h = yarl_get_height(yarl);
        int stride = 3;
        fprintf(f, "P6 %d %d %d\n", w, h, 255);
        fwrite(yarl_get_buffer(yarl), 1, w * h * stride, f);

        fclose(f);
    }

    free(buffer);
    return 0;
}
