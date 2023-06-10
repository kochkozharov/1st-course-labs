#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>

typedef struct {
    ptrdiff_t col;
    long long value;
    ptrdiff_t next; //-1
} _Elem;

typedef struct {
    ptrdiff_t *m; //-1
    _Elem *a;         
    size_t size1, size2, size, empty_count, capacity; // size - фактическое количество элементов, capacity - кол-во выделенных ячеек для эл-тов.  empty_count - количество элементов, отмеченных как удаленные
    ptrdiff_t empty; //индекс первого в цепочке удаленных эл-тов
} Matrix;

void matrixClear(Matrix *matrix);

void matrixCreate(Matrix *matrix);

void matrixDestroy(Matrix *matrix);

bool matrixIsSquare(const Matrix *matrix);

int matrixDebugPrint(FILE *out, const Matrix *matrix);

int matrixPrint(FILE *out, const Matrix *matrix);

int matrixResize(Matrix *matrix, size_t size1, size_t size2);

int matrixScan(FILE *in, Matrix *matrix);

int matrixGet(const Matrix *matrix, size_t index1, size_t index2, long long *ptr);

int matrixSet(Matrix *matrix, size_t index1, size_t index2, long long value);

size_t matrixSize1(const Matrix *matrix);

size_t matrixSize2(const Matrix *matrix);

size_t matrixNonZeroCount(const Matrix *matrix);

int matrixCrossDivide(Matrix *matrix, long long value);

#endif //MATRIX_H
