#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/limits.h>
#include <sys/stat.h>

#include <yarl.h>

#include "examples.c"

#define DIRNAME "gallery"

int main(void) {

    Yarl yarl = yarl_init(500, 500);

    for (size_t i=0; i < examples_size; ++i) {
        examples[i].fn(yarl);
        char buf[PATH_MAX] = { 0 };
        mkdir(DIRNAME, 0777);
        snprintf(buf, sizeof(buf), DIRNAME "/%s.ppm", examples[i].name);
        int ret = yarl_render_ppm(yarl, buf);
        assert(ret == 0);
    }

    yarl_destroy(yarl);

    return 0;
}
