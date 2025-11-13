#include <stdio.h>

int main(void)
{
    FILE  *fp;
    char fname[FILENAME_MAX];

    printf("ファイル名:\n");
    scanf ("%s", fname);
    fp = fopen(fname, "r");
    
    if((fp = fopen(fname, "r")) == NULL)
        printf("\a そのファイルは存在しません。\n");
    else
        printf("そのファイルは存在します。");

    return 0;
}


