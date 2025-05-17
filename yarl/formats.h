#ifndef _FORMATS_H
#define _FORMATS_H

#include <assert.h>
#include <stddef.h>

#include "yarl.h"


//
// Utility functions for converting between specific color formats and the
// generic `YarlColor` type
//


// create a color struct from the given binary buffer, obeying the given `format`
static inline YarlColor color_from_buffer(unsigned char *buffer, YarlColorFormat format) {
    switch (format) {
        case YARL_COLOR_FORMAT_ARGB: return (YarlColor) {
            .a = buffer[0],
            .r = buffer[1],
            .g = buffer[2],
            .b = buffer[3],
        };
        case YARL_COLOR_FORMAT_ABGR: return (YarlColor) {
            .a = buffer[0],
            .r = buffer[3],
            .g = buffer[2],
            .b = buffer[1],
        };
        case YARL_COLOR_FORMAT_RGBA: return (YarlColor) {
            .r = buffer[0],
            .g = buffer[1],
            .b = buffer[2],
            .a = buffer[3],
        };
        case YARL_COLOR_FORMAT_BGRA: return (YarlColor) {
            .r = buffer[2],
            .g = buffer[1],
            .b = buffer[0],
            .a = buffer[3],
        };
        case YARL_COLOR_FORMAT_RGB: return (YarlColor) {
            .r = buffer[0],
            .g = buffer[1],
            .b = buffer[2],
        };
        case YARL_COLOR_FORMAT_BGR: return (YarlColor) {
            .r = buffer[2],
            .g = buffer[1],
            .b = buffer[0],
        };
        default:
            assert(!"unknown color format");
    }
}

// Writes `color` into `buffer`, obeying the given `format`
static inline void color_to_buffer(unsigned char *buffer, YarlColor color, YarlColorFormat format) {
    switch (format) {
        case YARL_COLOR_FORMAT_ARGB:
            buffer[0] = color.a;
            buffer[1] = color.r;
            buffer[2] = color.g;
            buffer[3] = color.b;
            break;
        case YARL_COLOR_FORMAT_ABGR:
            buffer[0] = color.a;
            buffer[3] = color.r;
            buffer[2] = color.g;
            buffer[1] = color.b;
            break;
        case YARL_COLOR_FORMAT_RGBA:
            buffer[0] = color.r;
            buffer[1] = color.g;
            buffer[2] = color.b;
            buffer[3] = color.a;
            break;
        case YARL_COLOR_FORMAT_BGRA:
            buffer[2] = color.r;
            buffer[1] = color.g;
            buffer[0] = color.b;
            buffer[3] = color.a;
            break;
        case YARL_COLOR_FORMAT_RGB:
            buffer[0] = color.r;
            buffer[1] = color.g;
            buffer[2] = color.b;
            break;
        case YARL_COLOR_FORMAT_BGR:
            buffer[2] = color.r;
            buffer[1] = color.g;
            buffer[0] = color.b;
            break;
        default:
            assert(!"unknown color format");
    }
}


#endif // _FORMATS_H
