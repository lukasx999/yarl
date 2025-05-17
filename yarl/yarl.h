#ifndef _YARL_H
#define _YARL_H

//
// Yarl Color Utilities
//

// Generic, format agnostic color type
typedef struct {
    unsigned char r; // red
    unsigned char g; // green
    unsigned char b; // blue
    unsigned char a; // alpha (may be neglected if not present withing to current format)
} YarlColor;

typedef enum {
    YARL_COLOR_FORMAT_ARGB,
    YARL_COLOR_FORMAT_ABGR,
    YARL_COLOR_FORMAT_RGBA,
    YARL_COLOR_FORMAT_BGRA,
    YARL_COLOR_FORMAT_RGB,
    YARL_COLOR_FORMAT_BGR,
} YarlColorFormat;

#define YARL_COLOR(rr, gg, bb, aa) ((YarlColor) { .r = (rr), .g = (gg), .b = (bb), .a = (aa) })

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

typedef struct Yarl Yarl;


//
// Yarl State Management
//

// Returns NULL on failure
Yarl          *yarl_init_buffer(unsigned char *canvas, int width, int height, YarlColorFormat format);
// Returns NULL on failure
// Allocates a new (zeroed) buffer using malloc()
Yarl          *yarl_init(int width, int height, YarlColorFormat format);
YarlColor      yarl_get_pixel   (const Yarl *yarl, int x, int y);
unsigned char *yarl_get_buffer(const Yarl *yarl);
int            yarl_get_width   (const Yarl *yarl);
int            yarl_get_height  (const Yarl *yarl);
// should only be called if automatic initialization was chosen using yarl_init()
void           yarl_destroy     (Yarl *yarl);
int            yarl_get_format_stride(YarlColorFormat format);


///////////////////////////////////////////////////////////////////////////////
// Yarl Drawing API
///////////////////////////////////////////////////////////////////////////////

void yarl_fill                  (Yarl *yarl, YarlColor color);
void yarl_draw_pixel            (Yarl *yarl, int x, int y, YarlColor color);
void yarl_draw_rect             (Yarl *yarl, int x, int y, int w, int h, YarlColor color);
void yarl_draw_rect_outline     (Yarl *yarl, int x, int y, int w, int h, YarlColor color);
/// angle and rot_count are in degrees
void yarl_draw_arc_outline      (Yarl *yarl, int cx, int cy, int r, float start_angle, float rot_count, YarlColor color);
/// angle and rot_count are in degrees
void yarl_draw_arc              (Yarl *yarl, int cx, int cy, int r, float start_angle, float rot_count, YarlColor color);
void yarl_draw_circle           (Yarl *yarl, int cx, int cy, int r, YarlColor color);
void yarl_draw_circle_outline   (Yarl *yarl, int cx, int cy, int r, YarlColor color);
void yarl_draw_ellipse          (Yarl *yarl, int x, int y, int rx, int ry, YarlColor color);
void yarl_draw_line             (Yarl *yarl, int x0, int y0, int x1, int y1, YarlColor color);
void yarl_draw_line_thick       (Yarl *yarl, int x0, int y0, int x1, int y1, YarlColor color, int thickness);
void yarl_draw_triangle         (Yarl *yarl, int x0, int y0, int x1, int y1, int x2, int y2, YarlColor color);



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
