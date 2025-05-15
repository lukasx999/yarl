#ifndef _YARL_H
#define _YARL_H

//
// Yarl Color Utilities
//

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} YarlColor;

#define YARL_COLOR(r, g, b, a) ((YarlColor) { (r), (g), (b), (a) })

#define YARL_WHITE              YARL_COLOR(0xff, 0xff, 0xff, 0xff)
#define YARL_RED                YARL_COLOR(0xff, 0x00, 0x00, 0xff)
#define YARL_DARK_RED           YARL_COLOR(0x8B, 0x00, 0x00, 0xff)
#define YARL_DARK_GREEN         YARL_COLOR(0x00, 0x64, 0x00, 0xff)
#define YARL_DARK_BLUE          YARL_COLOR(0x00, 0x00, 0x8B, 0xff)
#define YARL_DARK_YELLOW        YARL_COLOR(0xBA, 0x8E, 0x23, 0xff)
#define YARL_DARK_PURPLE        YARL_COLOR(0x30, 0x19, 0x34, 0xff)
#define YARL_BLACK              YARL_COLOR(0x00, 0x00, 0x00, 0xff)
#define YARL_GREEN              YARL_COLOR(0x00, 0xff, 0x00, 0xff)
#define YARL_BLUE               YARL_COLOR(0x00, 0x00, 0xff, 0xff)
#define YARL_CYAN               YARL_COLOR(0x00, 0xff, 0xff, 0xff)
#define YARL_YELLOW             YARL_COLOR(0xff, 0xff, 0x00, 0xff)
#define YARL_PINK               YARL_COLOR(0xff, 0x00, 0xff, 0xff)
#define YARL_PURPLE             YARL_COLOR(0x80, 0x00, 0x80, 0xff)
#define YARL_GREY               YARL_COLOR(0x80, 0x80, 0x80, 0xff)



//
// Yarl Types
//


typedef struct YarlContext* Yarl;

//
// Yarl State Management
//

/// Returns `NULL` on failure
Yarl yarl_with_buffer(YarlColor **canvas, int width, int height);
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


// returns -1 on error
int yarl_render_ppm(const Yarl yarl, const char *filename);


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
