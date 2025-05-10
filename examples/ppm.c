#include <yarl.h>
#include <backend/ppm.h>

#include "examples.c"

int main(void) {

    Yarl yarl = yarl_init(500, 500);

    for (size_t i=0; i < examples_size; ++i) {
        examples[i].fn(yarl);
        char buf[128] = { 0 };
        snprintf(buf, 128, "gallery/%s.ppm", examples[i].name);
        yarl_render_ppm(yarl, buf);
    }

    yarl_destroy(yarl);

    return 0;
}
