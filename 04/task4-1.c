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

    //条件分岐
    if(num2 > max)
        max = num2;
    if(num3 > max)
        max = num3;

    if(num2 < min)
        min = num2;
    if(num3 < min)
        min = num3;

    //出力
    printf("最大値は%fです。\n",max );
    printf("最小値は%fです。\n",min );
    return 0;
    
}


