#include <stdio.h>

struct xyz{
    int x;
    long y;
    double z;
};


struct xyz scan_xyz(){
    struct xyz temp;
    printf("x = ");      scanf("%d", &temp.x);
    printf("y = ");      scanf("%ld", &temp.y);
    printf("z = ");     scanf("%lf", &temp.z);

    return temp;
};

int main(void)
{
    struct xyz s;

    s = scan_xyz();

    printf("xyz.x = %d\n", s.x);
    printf("xyz.y = %ld\n", s.y);
    printf("xyz.z = %lf\n", s.z);

    
}


