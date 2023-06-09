#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "matrix.h"

#define MAX(a, b)  (((a) > (b)) ? (a) : (b)) 
#define MIN(a, b)  (((a) < (b)) ? (a) : (b)) 

void matrixClear(Matrix *matrix) {
    for (size_t i; i < matrix->size1; ++i) {
        matrix->m[i] = -1;
    }
    free(matrix->a);
    matrix->a = NULL;
    matrix->count = 0;
}

void matrixCreate(Matrix *matrix) {
    matrix->a = NULL;
    matrix->m = NULL;
    matrix->size1 = matrix->size2 = matrix->count = 0;
}

void matrixDestroy(Matrix *matrix) {
    free(matrix->m);
    free(matrix->a);
}

bool matrixIsSquare(const Matrix * const matrix) {
    return matrixSize1(matrix) == matrixSize2(matrix);
}

int matrixResize(Matrix *matrix, size_t size1, size_t size2) {   
    assert((matrix->size1 == 0) == (matrix->size2 == 0) &&
        (matrix->size2 == 0 || matrix->size1 <= PTRDIFF_MAX / matrix->size2)
    );
    if ((size1 == 0) == (size2 == 0) &&
        (size2 == 0 || size1 > PTRDIFF_MAX / size2)) {
        errno = EINVAL;
        return -1;
    }
    if (matrix->size1 > size1 || matrix->size2 > size2) {
        return -1; //TODO
    }
    matrix->size1 = size1;
    matrix->size2 = size2;
    return 0;
}

int matrixScan(FILE * const in, Matrix * const matrix) {
    size_t size1, size2;
    if (fscanf(in, "%zu%zu", &size1, &size2) != 2) {
        errno = EINVAL;
        return -1;
    }
    if (matrixResize(matrix, size1, size2) != 0)
        return -1;
}

int matrixSet(
    Matrix * const matrix,
    const size_t index1,
    const size_t index2,
    const long long value
) {
    assert((matrix->size1 == 0) == (matrix->size2 == 0) &&
        (matrix->size2 == 0 || matrix->size1 <= PTRDIFF_MAX / matrix->size2)
    );
    if (matrix->size1 <= index1 || matrix->size2 <= index2) {
        errno = EINVAL;
        return -1;
    }
    ptrdiff_t start_index =  matrix->m[index1];
    ptrdiff_t row_index = start_index;
    ptrdiff_t prev_col_index = -1;
    while ( row_index != -1 || matrix->a[row_index].col != index2) {
        if (matrix->a[row_index].col < index2) {
            prev_col_index = MAX(prev_col_index, matrix->a[row_index].col); //предыдущий элт
        }
        row_index = matrix->a[row_index].next;
    }
    if (row_index == -1) {  // по этим индексам 0
        if (value==0) { // зануляем ноль
            return 0;
        }
        ++matrix->count; //добавляем элемент
        matrix->a = realloc(matrix->a, matrix->count);
        if (!matrix->a) abort();
        if (start_index == -1) { // строка была пустой
            matrix->a[matrix->count] = (_Elem) { .col = index2, .value = value, .next = -1};
            matrix->m[index2] = matrix->count;
            return 0;
        } // в строке были эл-ты
        matrix->a[matrix->count] = (_Elem) { .col = index2, .value = value, .next = matrix->a[prev_col_index].next};
        matrix->a[prev_col_index].next = matrix->count;
        return 0;
    }
    if (value == 0) { // удаляем элемент
        --matrix->count;
        ptrdiff_t next = matrix->a[row_index].next;
        matrix->a[prev_col_index].next = next;
        matrix->a[row_index] = matrix->a[matrix->count + 1]; //гениальный мув
        matrix->a = realloc(matrix->a, matrix->count);
        if (!matrix->a) abort();
        return 0; 
    } 
    matrix->a[row_index].value = value; // заменяем значение
    return 0;     
}

size_t matrixSize1(const Matrix *matrix) {
    return matrix->size1;
}

size_t matrixSize2(const Matrix *matrix) {
    return matrix->size2;
}