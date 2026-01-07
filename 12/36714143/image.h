#ifndef IMAGE_H
#define IMAGE_H

#include <stdbool.h>

typedef struct {
    int width;
    int height;
    int channels;
    unsigned char *data;
    bool from_stb;
} Image;

bool load_image(const char *filename, Image *img);
bool save_png(const char *filename, const Image *img);
void free_image(Image *img);

#endif
