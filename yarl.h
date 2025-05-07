#ifndef _YARL_H
#define _YARL_H

#define RED   0xff0000ff
#define GREEN 0x00ff00ff
#define BLUE  0x0000ffff
#define PINK  0xff00ffff
#define WHITE 0xffffffff

typedef unsigned int color_t;

typedef struct YarlCanvas* Yarl;

Yarl yarl_canvas_create(int width, int height);
color_t **yarl_get_canvas(const Yarl yarl);
int yarl_get_canvas_width(const Yarl yarl);
int yarl_get_canvas_height(const Yarl yarl);
void yarl_canvas_destroy(Yarl yc);

void clear(Yarl yarl, color_t color);
void rect(Yarl yarl, int x, int y, int w, int h, color_t color);
void circle(Yarl yarl, int cx, int cy, int r, color_t color);
void line(Yarl yarl, int x0, int y0, int x1, int y1, color_t color);

#endif // _YARL_H
