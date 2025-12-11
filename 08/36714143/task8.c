#include <stdio.h>  //std input output
#include <stdlib.h> //std library
#include <string.h> //文字列走査用ライブラリ

#define MAX_FILENAME 256    //ファイル名を最大256文字まで格納できるよ
#define MAX_LINE 1024   //一行あたり1024まで扱えるよ

/*===========================
  構造体
===========================*/
typedef struct {
    char filename[MAX_FILENAME];
    int width;
    int height;
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

/*===========================
  関数プロトタイプ
  🐒「& は住所を取る、* は住所の中身を見る！」
  構造体ポインタ（-> のやつ）
  2重ポインタ（**p）
===========================*/

// 1. ファイル名から画像サイズを読み取る
void parse_image_size(Image *img);


// 2. ASCIIアート読み込み
AsciiArt load_ascii(const char *path);

// 3. ASCIIアート解放
void free_ascii(AsciiArt *art);

// 4. Twitterトリミング計算
CropArea compute_twitter_crop(Image img, float ratio_w, float ratio_h);

// 5. ASCII + トリミング枠のプレビュー表示
void render_ascii_preview(const AsciiArt *art, const CropArea *crop, const Image *img);

// 6. ファイル出力
void save_preview_to_file(const char *out, const AsciiArt *art,
                          const CropArea *crop, const Image *img);


/*===========================
  main（エントリーポイント）
===========================*/
int main(void) {
    Image img;
    AsciiArt ascii;
    CropArea crop;

    char ascii_path[MAX_FILENAME];

    /* --- 入力受付 --- */
    printf("画像ファイル名を入力してください（例：photo_1080x1350.jpg）: ");
    scanf("%s", img.filename);
    

    printf("ASCIIアートのファイルパス: ");
    scanf("%s", ascii_path);

    // /* --- 画像サイズの解析 --- */
    parse_image_size(&img);
    printf("画像サイズを取得: %d x %d\n", img.width, img.height);

    // /* --- ASCII読み込み --- */
    // ascii = load_ascii(ascii_path);
    // printf("ASCIIアート読み込み完了: %d 行\n", ascii.line_count);

    // /* --- Twitterトリミング（例：4:5） --- */
    // crop = compute_twitter_crop(img, 4, 5);
    // printf("トリミング領域: x=%d y=%d w=%d h=%d\n",
    //        crop.crop_x, crop.crop_y, crop.crop_w, crop.crop_h);

    // /* --- プレビュー表示 --- */
    // render_ascii_preview(&ascii, &crop, &img);

    // /* --- ファイル出力 --- */
    // save_preview_to_file("preview.txt", &ascii, &crop, &img);
    // printf("preview.txt に保存しました。\n");

    // /* --- メモリ解放 --- */
    // free_ascii(&ascii);

    return 0;
}

/*===========================
  関数の中身（あとで埋める）
===========================*/

// 画像名から 1234x567 の部分を読む
void parse_image_size(Image *img) {
    // TODO: sscanfで width, height を抽出
    //入力がphoto_1080x1350.jpgみたいになったとき画像サイズの数字だけ読み取りたい
    //文字列からデータを取り出す
    sscanf(img->filename, "%*[^0-9]%dx%d", &(img->width), &img->height);

}


// ASCIIアート読み込み
AsciiArt load_ascii(const char *path) {
    AsciiArt art = {0};

    // TODO: 行数を数える → mallocで確保 → 読み込み

    return art;
}

// ASCIIメモリ解放
void free_ascii(AsciiArt *art) {
    // TODO: 各行 free → art->lines free
}

// トリミング領域計算
CropArea compute_twitter_crop(Image img, float ratio_w, float ratio_h) {
    CropArea crop = {0};

    // TODO: 中心クロップの計算式を書く
    return crop;
}

// プレビュー表示
void render_ascii_preview(const AsciiArt *art, const CropArea *crop, const Image *img) {
    // TODO: ASCIIを中央合わせで & トリミング枠を重ねて表示
}

// ファイルに保存
void save_preview_to_file(const char *out, const AsciiArt *art,
                          const CropArea *crop, const Image *img) {
    // TODO: ファイル出力
}




// load_ascii()
// parse_image_size()
// compute_crop()
// render_ascii_preview()
// render_cropped_output()
// save_file()

