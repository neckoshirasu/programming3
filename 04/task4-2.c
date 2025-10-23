#include <stdio.h>

int main(void)
{
    double num1, num2, num3;

    //キーボードから入力
    printf("3つの実数値を入力せよ\n");
    printf("num1 = ");   scanf("%lf", &num1);
    printf("num2 = ");   scanf("%lf", &num2);
    printf("num3 = ");   scanf("%lf", &num3);

    //最大値,最小値の変数の作成
    double max = num1; 
    double min = num1;

    //num1,num2の比較
    switch (num2 < max){
        case 0: max = num2; break;  //maxの更新
        case 1: min = num2; break;  //minの更新
    }

    //num3とmax,minの比較
    switch (num3 < max){
        case 0: max = num3; break;  //num3が一番大きい
        case 1:
        switch (min > num3){
            case 0: ; break;    //num3は真ん中
            case 1: min = num3; break;  //num3は最小
        }
    }
        
    printf("最大値は%fです。\n",max );
    printf("最小値は%fです。\n",min );
    return 0;
 
    
}