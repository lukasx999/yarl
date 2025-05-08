#ifndef _YARL_H
#define _YARL_H

#define YARL_RED   0xff0000ff
#define YARL_GREEN 0x00ff00ff
#define YARL_BLUE  0x0000ffff
#define YARL_PINK  0xff00ffff
#define YARL_WHITE 0xffffffff

typedef unsigned int YarlColor;

typedef struct YarlContext* Yarl;

Yarl yarl_init(int width, int height);
YarlColor yarl_get_pixel(const Yarl yarl, int x, int y);
int yarl_get_width(const Yarl yarl);
int yarl_get_height(const Yarl yarl);
void yarl_destroy(Yarl yc);

void yarl_clear(Yarl yarl, YarlColor color);
void yarl_draw_point(Yarl yarl, int x, int y, YarlColor color);
void yarl_draw_rect(Yarl yarl, int x, int y, int w, int h, YarlColor color);
void yarl_draw_circle(Yarl yarl, int cx, int cy, int r, YarlColor color);
void yarl_draw_line(Yarl yarl, int x0, int y0, int x1, int y1, YarlColor color);

#endif // _YARL_H
