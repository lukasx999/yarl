#include <stdint.h>

#include "./yarl/yarl.h"

int main(void) {

    unsigned char buffer[500*500] = { 0 };
    Yarl *yarl = yarl_init_buffer(buffer, 500, 500, YARL_COLOR_FORMAT_RGB);
    (void) yarl;

    return 0;
}
