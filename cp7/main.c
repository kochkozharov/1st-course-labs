#include <stdio.h>

#include "matrix.h"

int main(void) {
    Matrix m;
    matrixCreate(&m);
    matrixResize(&m, 3, 4);
    matrixSet(&m, 0, 3, 343);
    matrixSet(&m, 0, 3, 344);
    matrixSet(&m, 0, 3, 0); //!!!
    matrixSet(&m, 0, 3, 343);
    matrixSet(&m, 1, 3, 6);
    matrixSet(&m, 0, 3, 0);
    matrixSet(&m, 2, 3, -4);
    matrixSet(&m, 2, 2, -100);
    matrixSet(&m, 2, 3, 0);
    matrixSet(&m, 2, 2, 0);
    matrixSet(&m, 1, 3, 0);
    printf("udal\n");
    matrixSet(&m, 0, 1, 3);
    matrixSet(&m, 0, 2, 7);
    matrixSet(&m, 0, 3, 8);
    matrixSet(&m, 1, 0, 1);
    matrixSet(&m, 0, 0, 2);
    matrixSet(&m, 1, 3, -66);
    matrixSet(&m, 2, 0, -66);

    printf("%ld\n", matrixNonZeroCount(&m));
    matrixDestroy(&m);

    return 0;
}
