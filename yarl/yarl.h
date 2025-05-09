#ifndef _YARL_H
#define _YARL_H

#define YARL_BLACK  0x00000000
#define YARL_WHITE  0xffffffff
#define YARL_RED    0xff0000ff
#define YARL_GREEN  0x00ff00ff
#define YARL_BLUE   0x0000ffff
#define YARL_CYAN   0x00ffffff
#define YARL_YELLOW 0xffff00ff
#define YARL_PINK   0xff00ffff
#define YARL_PURPLE 0x800080ff

// 4 bytes: 1. red, 2. green, 3. blue, 4. alpha
// alpha may be discarded on platforms that dont support it
typedef unsigned int YarlColor;

typedef struct YarlContext* Yarl;

Yarl yarl_init(int width, int height);
YarlColor yarl_get_pixel(const Yarl yarl, int x, int y);
// Returns the last index, instead of the total width, to stop users from making off-by-one errors
int yarl_get_width(const Yarl yarl);
// Returns the last index, instead of the total width, to stop users from making off-by-one errors
int yarl_get_height(const Yarl yarl);
void yarl_destroy(Yarl yc);

void yarl_clear                 (Yarl yarl, YarlColor color);
void yarl_draw_point            (Yarl yarl, int x, int y, YarlColor color);
void yarl_draw_rect             (Yarl yarl, int x, int y, int w, int h, YarlColor color);
void yarl_draw_rect_outline     (Yarl yarl, int x, int y, int w, int h, YarlColor color);
void yarl_draw_circle           (Yarl yarl, int cx, int cy, int r, YarlColor color);
void yarl_draw_circle_outline   (Yarl yarl, int cx, int cy, int r, YarlColor color);
void yarl_draw_ellipse          (Yarl yarl, int x, int y, int rx, int ry, YarlColor color);
void yarl_draw_line             (Yarl yarl, int x0, int y0, int x1, int y1, YarlColor color);
void yarl_draw_triangle_outline (Yarl yarl, int x0, int y0, int x1, int y1, int x2, int y2, YarlColor color);
void yarl_draw_line_thick(Yarl yarl, int x0, int y0, int x1, int y1, YarlColor color, int thickness);

#endif // _YARL_H
