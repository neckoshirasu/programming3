#include <stdio.h>  //std input output
#include <stdlib.h> //std library
#include <string.h> //文字列走査用ライブラリ
#include <stdbool.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define MAX_LINE 1024   //一行あたり1024まで扱えるよ


//構造体
typedef struct {
    int width;
    int height;
    int channels;
    unsigned char *data;
    bool from_stb;
} Image;

typedef struct {
    char **lines;      // 各行へのポインタ
    int line_count;    // 行数
    int max_width;     // 最長行幅
} AsciiArt;

typedef struct {
    int crop_x;
    int crop_y;
    int crop_w;
    int crop_h;
} CropArea;


//関数プロトタイプ
bool load_image(const char *filename, Image *img);
AsciiArt load_ascii(const char *path);

CropArea compute_twitter_crop(Image *img);

Image ascii_to_image(const AsciiArt *ascii, int char_w, int char_h);
Image crop_image(const Image *src, const CropArea *crop);
Image concat_vertical(const Image *top, const Image *bottom);

void free_image(Image *img);
void free_ascii(AsciiArt *art);
bool save_png(const char *filename, const Image *img);



//main（エントリーポイント）

int main(void) {

    Image img = {0};
    Image  ascii_img, cropped, final;
    AsciiArt ascii;
    CropArea crop;
    char filename[256];
    char ascii_path[256];
    char res[8];   // "yes" / "no" が入れば十分

    printf("画像ファイル名を入力してください: ");
    scanf("%255s", filename); 
    if (!load_image(filename, &img)) {
        return 1;  // 読み込み失敗
    }

    printf("画像読み込み成功！\n");
    printf("width=%d height=%d channels=%d\n",img.width, img.height, img.channels);
    
    printf("トリミングした画像の上にaciiアートを表示させますか？yes or no");
    scanf("%s", res);

    if (strcmp(res, "yes") == 0) {

        printf("ASCIIアートのファイルパス: ");
        scanf("%s", ascii_path);
        
        ascii = load_ascii(ascii_path);
        printf("ASCIIアート読み込み完了: %d 行\n", ascii.line_count);

        crop = compute_twitter_crop(&img);
        printf("トリミング領域: x=%d y=%d w=%d h=%d\n", crop.crop_x, crop.crop_y, crop.crop_w, crop.crop_h);

        if (ascii.max_width <= 0) {
            fprintf(stderr, "ASCIIの横幅が0です（ファイル内容を確認してください）\n");
            free_image(&img);
            free_ascii(&ascii);
            return 1;
        }

        //トリミング画像生成
        cropped = crop_image(&img, &crop);

        // crop_image 
        if (cropped.channels == 4) {
            Image rgb;
            rgb.width = cropped.width;
            rgb.height = cropped.height;
            rgb.channels = 3;
            rgb.data = malloc(rgb.width * rgb.height * 3);

            for (int i = 0; i < rgb.width * rgb.height; i++) {
                rgb.data[i*3+0] = cropped.data[i*4+0];
                rgb.data[i*3+1] = cropped.data[i*4+1];
                rgb.data[i*3+2] = cropped.data[i*4+2];
            }

            free(cropped.data);
            cropped = rgb;
        }
        
        //ASCIIサイズを写真に合わせる
        int char_w = cropped.width / ascii.max_width;
        if (char_w < 6) char_w = 6;
        int char_h = char_w * 2;
        printf("char size: %dx%d\n", char_w, char_h);
        
        ascii_img = ascii_to_image(&ascii, char_w, char_h);

        //上下合成
        final = concat_vertical(&ascii_img, &cropped);

        printf("ascii_img: %dx%d ch=%d\n",
            ascii_img.width, ascii_img.height, ascii_img.channels);
        printf("cropped: %dx%d ch=%d\n",
            cropped.width, cropped.height, cropped.channels);
        printf("final: %dx%d ch=%d\n",
            final.width, final.height, final.channels);


        //PNG 出力
        stbi_write_png(
            "final.png",
            final.width,
            final.height,
            final.channels,
            final.data,
            final.width * final.channels
        );

            printf("final.png を出力しました\n");
    }else{
        crop = compute_twitter_crop(&img);
        printf("トリミング領域: x=%d y=%d w=%d h=%d\n", crop.crop_x, crop.crop_y, crop.crop_w, crop.crop_h);

        
        //トリミング画像生成
        cropped = crop_image(&img, &crop);

        save_png("final.png",&cropped);

        printf("final.png を出力しました\n");   
    }


    
    //メモリ解放
    if (ascii_img.data) free(ascii_img.data);
    if (cropped.data)   free(cropped.data);
    if (final.data)     free(final.data);
    free_ascii(&ascii);

    return 0;
}

//関数たち

// 画像の部分を読む
bool load_image(const char *filename, Image *img) {
    img->data = stbi_load(
        filename,
        &img->width,
        &img->height,
        &img->channels,
        0
    );

    if (!img->data) {
        fprintf(stderr, "画像の読み込みに失敗しました\n");
        return false;
    }
    return true;
}

// ASCIIアート読み込み
AsciiArt load_ascii(const char *path) {
    AsciiArt art = {0};
    // TODO: 行数を数える → mallocで確保 → 読み込み
    FILE *fp;
    fp = fopen(path,"r");
    int line_count  = 0;
    char buffer[512];
    //行数を数える
    if(fp == NULL){     //ファイル操作
        printf("ファイルを開けれませんでした。\n");
        return art;
    }
    while(fgets(buffer,sizeof(buffer),fp)){
        line_count++;    //行数分カウント
    }
    fclose(fp);
    fp = fopen(path, "r");
    art.lines = malloc(sizeof(char*) * line_count);  //行のポインタ文のメモリを確保

    for(int i = 0; i < line_count ;i++){
        fgets(buffer,sizeof(buffer),fp);    //行の内容読み込み
        buffer[strcspn(buffer,"\n")] = '\0';
        int len = strlen(buffer);
        if(len > art.max_width){
            art.max_width = len;
        }
        art.lines[i] = malloc(len + 1);  //終端文字\0の分も確保
        strcpy(art.lines[i], buffer);     
    }
    // ファイルを閉じる
    fclose(fp);
    art.line_count = line_count;

    return art;
}

Image ascii_to_image(const AsciiArt *ascii, int char_w, int char_h) {
    Image img;
    img.width  = ascii->max_width * char_w;
    img.height = ascii->line_count * char_h;
    img.channels = 3;
    int offset_x = (img.width - ascii->max_width * char_w) / 2;


    img.data = calloc(img.width * img.height * img.channels, 1);

    for (int y = 0; y < ascii->line_count; y++) {
        for (int x = 0; x < strlen(ascii->lines[y]); x++) {
            if (ascii->lines[y][x] != ' ') {
                for (int py = 0; py < char_h; py++) {
                    for (int px = 0; px < char_w; px++) {
                        int ix = (y * char_h + py) * img.width
                               + (offset_x + x * char_w + px);
                        img.data[ix * 3 + 0] = 255;
                        img.data[ix * 3 + 1] = 255;
                        img.data[ix * 3 + 2] = 255;
                    }
                }
            }
        }
    }
    return img;
}

// ASCIIメモリ解放
void free_ascii(AsciiArt *art) {
    // TODO: 各行 free → art->lines free
    if (art == NULL || art->lines == NULL) {
        return;
    }
    for (int i = 0; i < art->line_count; i++) {
        free(art->lines[i]);
    }
    free(art->lines);

    art->lines = NULL;
    art->line_count = 0;
    art->max_width = 0;

}

// トリミング領域計算
CropArea compute_twitter_crop(Image *img ) {
    CropArea crop = {0};
    // TODO: 中心クロップの計算式を書く
    int height = img->height;
    int width = img->width;
    float aspect = (int)width/ height;


    //width, height は画像のピクセル数
    
    if(0.75 <= aspect && aspect <= 1.333){
        crop.crop_x = 0;
        crop.crop_y = 0;
        crop.crop_w = width;
        crop.crop_h = height;
        return crop;
    }
    if(aspect < 0.75f){   //縦長ちゃん
        //4:3にトリミング
        float target_ratio = 3.0f / 4.0f;  // 0.75
        crop.crop_w = width;    // 高さに合わせた幅
        crop.crop_h = (int)(width / target_ratio);
        crop.crop_x = 0;
        crop.crop_y = (height - crop.crop_h) / 2;

    }else{
        //3:4,9:16にトリミング
        float target_ratio = 9.0f / 16.0f; // 0.5625
        crop.crop_w = (int)(height * target_ratio);
        crop.crop_h = height; // 幅に合わせた高さ
        crop.crop_x = (width - crop.crop_w) / 2;
        crop.crop_y = 0;
    }

    if (crop.crop_x < 0) crop.crop_x = 0;
    if (crop.crop_y < 0) crop.crop_y = 0;
    if (crop.crop_x + crop.crop_w > width)
        crop.crop_w = width - crop.crop_x;
    if (crop.crop_y + crop.crop_h > height)
        crop.crop_h = height - crop.crop_y;

    return crop;
}

Image crop_image(const Image *src, const CropArea *crop) {
    Image out;
    out.width  = crop->crop_w;
    out.height = crop->crop_h;
    out.channels = src->channels;

    out.data = malloc(out.width * out.height * out.channels);
    if (!out.data) {
        out.width = out.height = 0;
        return out;
    }

    for (int y = 0; y < out.height; y++) {
        for (int x = 0; x < out.width; x++) {
            int src_x = crop->crop_x + x;
            int src_y = crop->crop_y + y;

            int src_i = (src_y * src->width + src_x) * src->channels;
            int dst_i = (y * out.width + x) * out.channels;

            for (int c = 0; c < src->channels; c++) {
                out.data[dst_i + c] = src->data[src_i + c];
            }
        }
    }
    return out;
}

bool save_png(const char *filename, const Image *img) {
    if (!img->data) return false;

    return stbi_write_png(
        filename,
        img->width,
        img->height,
        img->channels,
        img->data,
        img->width * img->channels
    );
}

Image concat_vertical(const Image *top, const Image *bottom) {
    Image out;
    out.width = (top->width > bottom->width) ? top->width : bottom->width;
    out.height = top->height + bottom->height;
    out.channels = 3;

    out.data = calloc(out.width * out.height * out.channels, 1);

    // 上（ASCII）
    for (int y = 0; y < top->height; y++) {
        memcpy(
            &out.data[y * out.width * 3],
            &top->data[y * top->width * 3],
            top->width * 3
        );
    }

    // 下（画像）
    for (int y = 0; y < bottom->height; y++) {
        memcpy(
            &out.data[(y + top->height) * out.width * 3],
            &bottom->data[y * bottom->width * 3],
            bottom->width * 3
        );
    }


    return out;
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
