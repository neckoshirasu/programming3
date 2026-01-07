#include "crop.h"
#include <stdlib.h>
#include <string.h>

/*
 * Twitter向け中央トリミング（16:9）
 */
CropArea compute_twitter_crop(Image *img) {
    CropArea crop = {0};

    int target_w = img->width;
    int target_h = img->width * 9 / 16;

    if (target_h > img->height) {
        target_h = img->height;
        target_w = img->height * 16 / 9;
    }

    crop.crop_w = target_w;
    crop.crop_h = target_h;
    crop.crop_x = (img->width  - target_w) / 2;
    crop.crop_y = (img->height - target_h) / 2;

    return crop;
}

/*
 * 画像を指定範囲で切り抜く
 */
Image crop_image(const Image *src, const CropArea *crop) {
    Image dst = {0};

    dst.width    = crop->crop_w;
    dst.height   = crop->crop_h;
    dst.channels = src->channels;
    dst.from_stb = false;

    int bytes = dst.width * dst.height * dst.channels;
    dst.data = malloc(bytes);

    for (int y = 0; y < dst.height; y++) {
        int src_y = crop->crop_y + y;
        memcpy(
            dst.data + y * dst.width * dst.channels,
            src->data + (src_y * src->width + crop->crop_x) * dst.channels,
            dst.width * dst.channels
        );
    }

    return dst;
}
