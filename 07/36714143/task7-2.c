#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES 

int main(void)
{
    FILE *fp;

    double x, y;
    double A = 1.0;

    //書き込むもーーど
    fp = fopen("sin.dat", "w");

    for(int i = 0; i < 100; i++){
        x = (double) i / 100.0;
        y = A * sin(2 * (M_PI)  * x);

        //ファイルに書き込み
        fprintf(fp, "%lf, %lf\n", x, y);        
    }

    fclose(fp);

    return 0;
}


