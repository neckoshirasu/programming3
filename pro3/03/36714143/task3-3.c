#include <stdio.h>

int main(void)
{
    printf("何人の教科の点数を読み込みますか？");
    int n;
    scanf("%d",&n);
    int test[n][2];

    //点数の読み込み
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 2; j++){
            printf("%d人目の%d科目目の教科 =",(i + 1),(j + 1));
            scanf("%d", &test[i][j]);
        }
    }
    int sum = 0;
    //科目ごとの合計/平均
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < n; j++){
            sum += test[j][i];
        }
        printf("%d科目の合計点は、%d点です\n",(i + 1),sum);
        printf("科目%dの平均点は、%f点です\n",(i + 1), (double)sum / n);
        sum = 0;
    }
    

    //学生ごとの合計点と平均点
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 2; j++){
            sum += test[i][j];
        }
        printf("%d人目の学生の合計点は、%d点です\n",(i + 1), sum);
        printf("%dの平均点は、%f点です\n",(i + 1), (double)sum / 2);
        sum = 0;
    }
    return 0;
}
