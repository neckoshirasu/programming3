#include <stdio.h>

int main(void)
{
    double num1, num2, num3;

    //キーボードから入力
    printf("3つの実数値を入力せよ\n");
    printf("num1 = ");   scanf("%lf", &num1);
    printf("num2 = ");   scanf("%lf", &num2);
    printf("num3 = ");   scanf("%lf", &num3);


    double max = num1; 
    double min = num1;

    switch (num2 < max){
        case 0: max = num2; break;
        case 1: min = num2; break;
    }


    switch (num3 < max){
        case 0: max = num3; break;
        case 1:
        switch (min > num3){
            case 0: ; break;
            case 1: min = num3; break;
        }
    }
        
    printf("最大値は%fです。\n",max );
    printf("最小値は%fです。\n",min );
    return 0;
 
    
}