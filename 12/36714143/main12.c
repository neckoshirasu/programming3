#include <stdio.h>
#include <string.h>
#include "image.h"
#include "ascii.h"
#include "crop.h"
#include "concat.h"

int main(void) {
    Image img = {0}, cropped, ascii_img, final;
    AsciiArt ascii;
    CropArea crop;

    char filename[256];
    char ascii_path[256];
    char res[8];

    printf("画像ファイル名: ");
    scanf("%255s", filename);

    if (!load_image(filename, &img)) return 1;

    printf("ASCIIを合成しますか？(yes/no): ");
    scanf("%7s", res);

    crop = compute_twitter_crop(&img);
    cropped = crop_image(&img, &crop);

    if (strcmp(res, "yes") == 0) {
        printf("ASCIIファイル: ");
        scanf("%255s", ascii_path);

        ascii = load_ascii(ascii_path);
        ascii_img = ascii_to_image(&ascii, 10, 20);
        final = concat_vertical(&ascii_img, &cropped);
        save_png("final.png", &final);

        free_ascii(&ascii);
        free_image(&ascii_img);
        free_image(&final);
    } else {
        save_png("final.png", &cropped);
    }

    free_image(&cropped);
    free_image(&img);
    return 0;
}
