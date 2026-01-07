#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    int *arr;

    printf("数字を入力してください: ");
    scanf("%d", &n);

    // 動的メモリ確保
    arr = (int *)malloc(sizeof(int) * n);
    if (arr == NULL) {
        printf("メモリ確保に失敗しました\n");
        return 1;
    }

    // 値の代入
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // 出力
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // メモリ解放
    free(arr);

    return 0;
}
