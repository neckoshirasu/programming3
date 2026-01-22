#include <stdio.h>
#include "task15-1.h"

int main(void) {
    // int n = 743;
    int n;  // 点数
    puts("データ点数");
    scanf("%d",&n);
    write_data("36714143-1.dat", func1, n);
    write_data("36714143-2.dat", func2, n);
    write_data("36714143-3.dat", func3, n);
    printf("データファイルを出力しました。\n");
    return 0;
}