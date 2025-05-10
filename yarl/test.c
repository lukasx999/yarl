#include <stdio.h>
#include <assert.h>

#include "yarl.h"

int main(void) {

    assert(YARL_COLOR_R(0xfafbfcfd) == 0xfa);
    assert(YARL_COLOR_G(0xfafbfcfd) == 0xfb);
    assert(YARL_COLOR_B(0xfafbfcfd) == 0xfc);
    assert(YARL_COLOR_A(0xfafbfcfd) == 0xfd);
    assert(yarl_lerp_color(0x00000000, 0xffffffff, 0.5) == 0x7f7f7f7f);

    return 0;
}
