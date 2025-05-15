#ifndef _YARL_H
#define _YARL_H

//
// Yarl Color Utilities
//

#define YARL_DARK_RED           0x8B0000ff
#define YARL_DARK_GREEN         0x006400ff
#define YARL_DARK_BLUE          0x00008Bff
#define YARL_DARK_YELLOW        0xBA8E23ff
#define YARL_DARK_PURPLE        0x301934ff
#define YARL_BLACK              0x000000ff
#define YARL_WHITE              0xffffffff
#define YARL_RED                0xff0000ff
#define YARL_GREEN              0x00ff00ff
#define YARL_BLUE               0x0000ffff
#define YARL_CYAN               0x00ffffff
#define YARL_YELLOW             0xffff00ff
#define YARL_PINK               0xff00ffff
#define YARL_PURPLE             0x800080ff
#define YARL_GREY               0x808080ff



//
// Yarl Types
//

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} YarlColor;

typedef struct YarlContext* Yarl;

//
// Yarl State Management
//

/// Returns `NULL` on failure
Yarl yarl_init(int width, int height);
YarlColor yarl_get_pixel(const Yarl yarl, int x, int y);
/// Returns the last index, instead of the total width, to stop users from making off-by-one errors
int yarl_get_width(const Yarl yarl);
/// Returns the last index, instead of the total width, to stop users from making off-by-one errors
int yarl_get_height(const Yarl yarl);
void yarl_destroy(Yarl yarl);
YarlColor **yarl_get_canvas(const Yarl yarl);



///////////////////////////////////////////////////////////////////////////////
// Yarl Drawing API
///////////////////////////////////////////////////////////////////////////////

void yarl_fill                  (Yarl yarl, YarlColor color);
void yarl_draw_point            (Yarl yarl, int x, int y, YarlColor color);
void yarl_draw_rect             (Yarl yarl, int x, int y, int w, int h, YarlColor color);
void yarl_draw_rect_outline     (Yarl yarl, int x, int y, int w, int h, YarlColor color);
/// angle and rot_count are in degrees
void yarl_draw_arc_outline      (Yarl yarl, int cx, int cy, int r, float start_angle, float rot_count, YarlColor color);
/// angle and rot_count are in degrees
void yarl_draw_arc              (Yarl yarl, int cx, int cy, int r, float start_angle, float rot_count, YarlColor color);
void yarl_draw_circle           (Yarl yarl, int cx, int cy, int r, YarlColor color);
void yarl_draw_circle_outline   (Yarl yarl, int cx, int cy, int r, YarlColor color);
void yarl_draw_ellipse          (Yarl yarl, int x, int y, int rx, int ry, YarlColor color);
void yarl_draw_line             (Yarl yarl, int x0, int y0, int x1, int y1, YarlColor color);
void yarl_draw_line_thick       (Yarl yarl, int x0, int y0, int x1, int y1, YarlColor color, int thickness);
void yarl_draw_triangle         (Yarl yarl, int x0, int y0, int x1, int y1, int x2, int y2, YarlColor color);



///////////////////////////////////////////////////////////////////////////////
// Yarl Utilities
///////////////////////////////////////////////////////////////////////////////

#define YARL_PI 3.14159265358979323846

#define YARL_CLAMP(value, min, max) \
    (assert(min <= max), \
    (value) > (max) ? (max) : (value) < (min) ? (min) : (value))

#define YARL_LERP(a, b, t) \
    ((a) + (t) * ((b) - (a)))

#define YARL_RAD_TO_DEG(rads) \
    ((rads) * (180. / YARL_PI))

#define YARL_DEG_TO_RAD(rads) \
    ((rads) * (YARL_PI / 180.))

YarlColor yarl_lerp_color(YarlColor a, YarlColor b, float t);

#endif // _YARL_H
