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
    matrixSet(&m, 0, 1, 3);
    matrixSet(&m, 0, 2, 7);
    matrixSet(&m, 0, 3, 8);
    matrixSet(&m, 1, 0, 1);
    matrixSet(&m, 0, 0, 2);
    matrixSet(&m, 1, 3, -66);
    matrixSet(&m, 2, 0, -66);
    matrixSet(&m, 2, 2, -88);
    matrixResize(&m, 2, 3);
    matrixSet(&m, 1, 2, 666);
    printf("Modified matrix:\n");
    matrixResize(&m,3,3);
    matrixDebugPrint(stdout, &m);
    matrixPrint(stdout,&m);
    matrixDestroy(&m);
    Matrix scnd_m;
    matrixCreate(&scnd_m);
    printf("Input matrix:\n");
    matrixScan(stdin, &scnd_m);
    matrixDebugPrint(stdout, &scnd_m);
    matrixPrint(stdout, &scnd_m);
    matrixCrossDivide(&scnd_m,-10);
    printf("Cross Divide:\n");
    matrixPrint(stdout, &scnd_m);
    matrixDestroy(&scnd_m);
    return 0;
}
