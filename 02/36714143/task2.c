#include <stdio.h>

int main(void)
{
    int num;

    printf("身長を入力せよ");
    scanf("%d", &num);
    double ans = (num - 100)* 0.9;
    printf("標準体重は%.1fです。\n",ans );

    return 0;


}
