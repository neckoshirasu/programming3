#include <stdio.h>

int main(void)
{
    int a[4][3];
    int b[3][4];
    
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            printf("a[%d][%d] = ", i, j);
            scanf(a[i][j]);
        }
    }

    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 4; j++){
            printf("b[%d][%d] = ", i, j);
            scanf(b[i][j]);
        }
    }
    return 0;
}
