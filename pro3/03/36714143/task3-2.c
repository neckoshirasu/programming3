#include <stdio.h>

int main(void)
{
    int a[4][3];
    int b[3][4];
    int c[4][4] = {0};
    
    //キーボードで配列を入力
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 3; j++){
            printf("a[%d][%d] = ", i, j);
            scanf("%d", &a[i][j]);

        }
            
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            printf("b[%d][%d] = ", i, j);
            scanf("%d", &b[i][j]);
        }
    }

    // 4*3 3*4の行列の積を計算
    for(int i = 0; i < 4;i++){
        for(int j =0; j < 4; j++){
            for(int k = 0; k < 3; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }

    //答えを出力
    printf("答えの行列は\n");
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            printf("c[%d][%d] = %d\n", i, j, c[i][j]);
        }
    }

    return 0;
}
