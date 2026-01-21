#include <stdio.h>
#include <math.h>
#include "task15-1.h"

#define PI 3.141592653589793

// y = sin(x^2)/x
double func1(double x) {
    if (x == 0) return 1.0; // 0除算回避
    return sin(x * x) / x;
}

// y = 1/x
double func2(double x) {
    if (x == 0) return 0.0;
    return 1.0 / x;
}

// y = -1/x
double func3(double x) {
    if (x == 0) return 0.0;
    return -1.0 / x;
}

// データ書き出し関数
void write_data(const char *filename, double (*func)(double), int n) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("ファイルオープン失敗");
        return;
    }

    double x, y;
    double dx = (2.0 * PI) / (n - 1);

    for (int i = 0; i < n; i++) {
        x = i * dx;
        y = func(x);
        fprintf(fp, "%lf %lf\n", x, y);
    }

    fclose(fp);
}