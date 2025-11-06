#include <stdio.h>

struct xyz{
    int x;
    long y;
    double z;
};


struct xyz scan_xyz(){
    struct xyz temp;
    scanf("x = %d\n", &temp.x);
    scanf("y = %ld\n", &temp.y);
    scanf("z = %lf", &temp.z);

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


