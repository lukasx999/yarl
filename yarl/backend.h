#ifndef _YARL_BACKEND_H
#define _YARL_BACKEND_H

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "yarl.h"

#include <raylib.h>

// TODO: get view into entire canvas instead of iterating

// TODO: OpenGL
// TODO: Xlib
// TODO: Wayland

void render_raylib(Yarl yarl, int x0, int y0, float scale);
void render_ppm(Yarl yarl, const char *filename);

#endif // _YARL_BACKEND_H
