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
CropArea compute_twitter_crop(Image *img);

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

    /* --- 入力受付 ---A */
    printf("画像ファイル名を入力してください（例：photo_1080x1350.jpg）: ");
    scanf("%s", img.filename);
    

    printf("ASCIIアートのファイルパス: ");
    scanf("%s", ascii_path);

    // /* --- 画像サイズの解析 --- */
    parse_image_size(&img);
    printf("画像サイズを取得: %d x %d\n", img.width, img.height);

    // /* --- ASCII読み込み --- */
    ascii = load_ascii(ascii_path);
    printf("ASCIIアート読み込み完了: %d 行\n", ascii.line_count);

    /* --- Twitterトリミング（例：4:5） --- */
    crop = compute_twitter_crop(&img);
    printf("トリミング領域: x=%d y=%d w=%d h=%d\n",
           crop.crop_x, crop.crop_y, crop.crop_w, crop.crop_h);

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

// ASCIIメモリ解放
void free_ascii(AsciiArt *art) {
    // TODO: 各行 free → art->lines free
}

// トリミング領域計算
CropArea compute_twitter_crop(Image *img ) {
    CropArea crop = {0};
    // TODO: 中心クロップの計算式を書く
    float height = img->height;
    float width = img->width;
    float aspect = width/ height;

    //width, height は画像のピクセル数
    

    if(0.75 <= aspect && aspect <= 1.333){
        crop.crop_x = 0;
        crop.crop_y = 0;
        crop.crop_w = width;
        crop.crop_h = height;
        return crop;
    }else if(aspect == 1.0){
        crop.crop_x = 0;
        crop.crop_y = 0;
        crop.crop_w = width;
        crop.crop_h = height;
        return crop;
    }else if(height > width){   //縦長ちゃん
        //4:3にトリミング
        float target_ratio = 4.0f / 3.0f;  // 0.75
        crop.crop_w = height * target_ratio;    // 高さに合わせた幅
        crop.crop_h = height;
        crop.crop_x = (width - crop.crop_w) / 2;
        crop.crop_y = 0;
        return crop;
    }else{
        //3:4,9:16にトリミング
        float target_ratio = 9.0f / 16.0f; // 0.5625
        crop.crop_w = width;
        crop.crop_h = width / target_ratio;   // 幅に合わせた高さ
        crop.crop_x = 0;
        crop.crop_y = (height - crop.crop_h) / 2;
        return crop;
    }
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

