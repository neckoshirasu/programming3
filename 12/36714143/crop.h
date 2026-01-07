#ifndef CROP_H
#define CROP_H

#include "image.h"

typedef struct {
    int crop_x;
    int crop_y;
    int crop_w;
    int crop_h;
} CropArea;

CropArea compute_twitter_crop(Image *img);
Image crop_image(const Image *src, const CropArea *crop);

#endif
