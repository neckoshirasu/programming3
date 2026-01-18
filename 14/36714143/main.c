#include <stdio.h>
#include <stdlib.h>
#include "task14.h"

int main(void) {
    int n;
    int *array;

    printf("数字を入力してください: ");
    scanf("%d", &n);

    array = create_array(n);
    if (array == NULL) {
        printf("メモリ確保に失敗しました\n");
        return 1;
    }

    print_array(array, n);

    free(array);
    return 0;
}
