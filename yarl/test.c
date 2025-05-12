#include <stdio.h>
#include <assert.h>

#include "yarl.h"
#include "util.h"

int main(void) {

    assert(YARL_COLOR_R(0xfafbfcfd) == 0xfa);
    assert(YARL_COLOR_G(0xfafbfcfd) == 0xfb);
    assert(YARL_COLOR_B(0xfafbfcfd) == 0xfc);
    assert(YARL_COLOR_A(0xfafbfcfd) == 0xfd);

    assert(yarl_lerp_color(0x00000000, 0xffffffff, 0.5) == 0x7f7f7f7f);

    assert(rotation_angle_around_center(5, 5)   == 315);
    assert(rotation_angle_around_center(5, -5)  == 45);
    assert(rotation_angle_around_center(-5, -5) == 135);
    assert(rotation_angle_around_center(-5, 5)  == 225);
    assert(rotation_angle_around_center(5, 0)   == 0);
    assert(rotation_angle_around_center(0, 5)   == 270);
    assert(rotation_angle_around_center(0, -5)  == 90);
    assert(rotation_angle_around_center(-5, 0)  == 180);

    return 0;
}
