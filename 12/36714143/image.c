#include "image.h"
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

bool load_image(const char *filename, Image *img) {
    img->data = stbi_load(filename, &img->width, &img->height, &img->channels, 0);
    img->from_stb = true;

    if (!img->data) {
        fprintf(stderr, "画像の読み込みに失敗しました\n");
        return false;
    }
    return true;
}

bool save_png(const char *filename, const Image *img) {
    return stbi_write_png(
        filename,
        img->width,
        img->height,
        img->channels,
        img->data,
        img->width * img->channels
    );
}

void free_image(Image *img) {
    if (!img || !img->data) return;

    if (img->from_stb) {
        stbi_image_free(img->data);
    } else {
        free(img->data);
    }
    img->data = NULL;
}
