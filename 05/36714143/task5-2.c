#include <stdio.h>

void gobai(int *a, int *b){
    *a = *a * 5;
    *b = *b * 5;
}

int main(void)
{
    int a, b;

    puts("2つの整数を入力せよ");
    printf("整数A:");   scanf("%d", &a);
    printf("整数B:");   scanf("%d", &b);
 
    gobai(&a, &b);

    printf("a = %d\n", a);
    printf("b = %d\n", b);
    return 0;
    
}


