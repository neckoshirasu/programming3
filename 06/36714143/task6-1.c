#include <stdio.h>

#define NAME_LEN    64

struct student{
    char name [NAME_LEN];
    int height;
    double weight;
};

int main(void)
{
    struct student takao = {"Takao", 173};
    
    printf("氏名のアドレス = %p\n", &takao.name);
    printf("身長のアドレス = %p\n", &takao.height);
    printf("体重のアドレス = %p\n", &takao.weight);
    
    return 0;
}


