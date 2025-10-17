#include <stdio.h>

int main(void)
{
    int num;

    printf("整数を入力せよ。");

    
    printf("整数を入力せよ。");
    printf("整数を入力せよ。");
    scanf("%d", &num);
    printf("%dの符号を反転した値は%dです。\n", +num, -num);

    return 0;
    
}
