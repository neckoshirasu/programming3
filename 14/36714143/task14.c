#include <stdio.h>
#include <stdlib.h>
#include "task14.h"

/* 配列を動的確保し n, n-1, ..., 1 を代入 */
int *create_array(int n) {
    int *arr = (int *)malloc(sizeof(int) * n);
    if (arr == NULL) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
    return arr;
}

/* 配列の中身を出力 */
void print_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
