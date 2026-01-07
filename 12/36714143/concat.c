#include "concat.h"
#include <stdlib.h>
#include <string.h>

/*
 * ASCIIアートを簡易的に画像化（白文字・黒背景）
 */
Image ascii_to_image(const AsciiArt *ascii, int char_w, int char_h) {
    Image img = {0};

    img.width  = ascii->max_width * char_w;
    img.height = ascii->line_count * char_h;
    img.channels = 3;
    img.from_stb = false;

    img.data = malloc(img.width * img.height * 3);

    // 黒で初期化
    memset(img.data, 0, img.width * img.height * 3);

    for (int y = 0; y < ascii->line_count; y++) {
        for (int x = 0; x < (int)strlen(ascii->lines[y]); x++) {

            unsigned char c = ascii->lines[y][x];
            if (c == ' ') continue;

            // 白ブロックで文字表現
            for (int dy = 0; dy < char_h; dy++) {
                for (int dx = 0; dx < char_w; dx++) {
                    int px = x * char_w + dx;
                    int py = y * char_h + dy;
                    int idx = (py * img.width + px) * 3;

                    img.data[idx + 0] = 255;
                    img.data[idx + 1] = 255;
                    img.data[idx + 2] = 255;
                }
            }
        }
    }
    return img;
}

/*
 * 上下方向に画像を結合
 */
Image concat_vertical(const Image *top, const Image *bottom) {
    Image out = {0};

    out.width  = (top->width > bottom->width) ? top->width : bottom->width;
    out.height = top->height + bottom->height;
    out.channels = top->channels;
    out.from_stb = false;

    out.data = malloc(out.width * out.height * out.channels);
    memset(out.data, 0, out.width * out.height * out.channels);

    // 上画像コピー
    for (int y = 0; y < top->height; y++) {
        memcpy(
            out.data + y * out.width * out.channels,
            top->data + y * top->width * top->channels,
            top->width * top->channels
        );
    }

    // 下画像コピー
    for (int y = 0; y < bottom->height; y++) {
        memcpy(
            out.data + (y + top->height) * out.width * out.channels,
            bottom->data + y * bottom->width * bottom->channels,
            bottom->width * bottom->channels
        );
    }

    return out;
}
