#ifndef CONCAT_H
#define CONCAT_H

#include "image.h"
#include "ascii.h"

Image ascii_to_image(const AsciiArt *ascii, int char_w, int char_h);
Image concat_vertical(const Image *top, const Image *bottom);

#endif
