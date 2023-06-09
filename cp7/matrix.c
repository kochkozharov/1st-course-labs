#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#define NDEBUG
#include <assert.h>

#include "matrix.h"


#define DEBUG   printf("M "); \
                for (size_t i = 0; i < matrix->size1; ++i) printf("%ld ", matrix->m[i]); \
                printf("\n"); \
                for (size_t i = 0; i < matrix->size; ++i) printf("%ld %lld %ld\n", matrix->a[i].col, matrix->a[i].value, matrix->a[i].next); \
                printf("\n"); 

#define MAX(a, b)  (((a) > (b)) ? (a) : (b)) 
#define MIN(a, b)  (((a) < (b)) ? (a) : (b)) 

static size_t newCapacity(const size_t capacity) {
    if (capacity == 0)
        return 1;
    return capacity <= SIZE_MAX / 2 ? capacity * 2 : SIZE_MAX;
}

void matrixClear(Matrix *matrix) { //занулить, сохравнив размер
    for (size_t i=0; i < matrix->size1; ++i) {
        matrix->m[i] = -1;
    }
    free(matrix->a);
    matrix->a = NULL;
    matrix->size = matrix->capacity = matrix->empty_count = 0;
    matrix->empty = -1;
}

void matrixCreate(Matrix *matrix) { //создается матрица 0x0 - ее нудно ресайзить
    matrix->a = NULL;
    matrix->m = NULL;
    matrix->size1 = matrix->size2 = matrix->size = matrix->capacity = matrix->empty_count= 0;
    matrix->empty = -1;
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
    if ((size1 == 0) != (size2 == 0) ||
        !(size2 == 0 || size1 <= PTRDIFF_MAX / size2)) {
        errno = EINVAL;
        return -1;
    }
    if (matrix->size1 > size1 || matrix->size2 > size2) {
        for (size_t i = 0; i < size1; ++i) {
            ptrdiff_t row_index =  matrix->m[i];
            ptrdiff_t prev_index = -1;
            while (  row_index != -1 ) {
                ptrdiff_t next = matrix->a[row_index].next;
                if ( (size_t) matrix->a[row_index].col >= size2) {
                    matrix->a[row_index].col = -1;
                    matrix->a[row_index].next = matrix->empty;
                    matrix->empty = row_index;
                    ++matrix->empty_count;
                    if (prev_index != -1) {
                        matrix->a[prev_index].next = next;
                    }
                }
                else {
                    prev_index = row_index;
                }
                row_index = next;
            }
        }
        for (size_t i = size1; i < matrix->size1; ++i) {
            ptrdiff_t row_index =  matrix->m[i];
            while (  row_index != -1 ) {
                matrix->a[row_index].col = -1;
                ptrdiff_t next = matrix->a[row_index].next;
                matrix->a[row_index].next = matrix->empty;
                matrix->empty = row_index;
                ++matrix->empty_count;
                row_index = next;
            }
        }
        matrix->size1 = size1;
        matrix->m=realloc(matrix->m, size1 * sizeof(size_t));
        if (!matrix->m) abort();
        matrix->size2 = size2;
        return 0; 
    }
    size_t old_size1 = matrix->size1;
    matrix->size1 = size1;
    matrix->size2 = size2;
    matrix->m = realloc(matrix->m, size1 * sizeof(size_t));
    if (!matrix->m) abort();
    for (size_t i=old_size1; i < matrix->size1; ++i) {
        matrix->m[i] = -1;
    }
    return 0;
}

int matrixScan(FILE * const in, Matrix * const matrix) {
    size_t size1, size2;
    if (fscanf(in, "%zu%zu", &size1, &size2) != 2) {
        errno = EINVAL;
        return -1;
    }
    if (matrixResize(matrix, size1, size2) != 0) {
        errno = EINVAL;
        return -1;
    }
    for (size_t i = 0; i < size1; ++i)
        for (size_t j = 0; j < size2; ++j) {
            long long value;
            if (fscanf(in, "%lld", &value) != 1)
                return -1;
            if (value != 0)
                matrixSet(matrix, i, j, value);
        }
    return 0;
}

int matrixDebugPrint(FILE *out, const Matrix *matrix) {
    if(fprintf(out, "size1 = %zu, size2 = %zu\n", matrix->size1, matrix->size2)<0)
        return -1;
    
    fprintf(out, "M = ");
    for (size_t i = 0; i < matrix->size1; ++i) {
        if(fprintf(out, "[%td]", matrix->m[i])<0)
            return -1;
    }
    fprintf(out, "\n");
    fprintf(out, "A = ");
    for (size_t i = 0; i < matrix->size; ++i) {
        if(fprintf(out, "[%td %lld %td]", matrix->a[i].col, matrix->a[i].value, matrix->a[i].next)<0)
            return -1;
    }
    fprintf(out, "\n");
    return 0;
}

int matrixPrint(FILE *out, const Matrix *matrix) {
    for (size_t  i = 0; i < matrix->size1; ++i) {
        for (size_t j=0; j < matrix->size2; ++j) {
            long long v;
            matrixGet(matrix, i, j, &v);
            if (fprintf(out, "\t%lld", v)  <  0 )
                return -1;
        }
        fprintf(out, "\n");
    }
    return 0;
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
    ptrdiff_t prev_index = -1;
    while ( matrix->a && row_index != -1 && (size_t) matrix->a[row_index].col != index2 ) {
        prev_index = row_index; // сохраняем предыдущий эл-т
        row_index = matrix->a[row_index].next;
    }
#ifndef NDEBUG
    printf("PREV COL IND %ld\n", prev_index);
#endif
    if (row_index == -1) {  // по этим индексам 0
        if (value==0) { // зануляем ноль
            return 0;
        }
        size_t index_in_a; //первый пустой или новый
        if (matrix->empty == -1) { //нет пробелов
            ++matrix->size; // реально добавляем элемент
            index_in_a = matrix->size-1;
            if (index_in_a == matrix->capacity) {
                matrix->capacity = newCapacity(matrix->capacity);
#ifndef NDEBUG
                printf("new cap: %ld\n", matrix->capacity);
                printf("%p\n", (void*) matrix->a);
#endif
                matrix->a = realloc(matrix->a, (matrix->capacity) * sizeof(_Elem));
                if (!matrix->a) abort();
            }
        }
        else { //или залатываем пробел
            --matrix->empty_count;
            index_in_a = matrix->empty;
            matrix->empty = matrix->a[matrix->empty].next;
        }
        if (start_index == -1) { // строка была пустой
            matrix->a[index_in_a] = (_Elem) { .col = index2, .value = value, .next = -1};
            matrix->m[index1] = index_in_a;
#ifndef NDEBUG
            DEBUG
#endif
            return 0;
        } // в строке были эл-ты
        matrix->a[index_in_a] = (_Elem) { .col = index2, .value = value, .next = matrix->a[prev_index].next};
        matrix->a[prev_index].next = index_in_a;
#ifndef NDEBUG
        DEBUG
#endif
        return 0;
    }
    if (value == 0) { // удаляем элемент      
        ++matrix->empty_count;
        ptrdiff_t next = matrix->a[row_index].next;
        if (start_index == row_index) { //элем был первым - обновляем m
            matrix->m[index1] = next;
        }
        else {
            matrix->a[prev_index].next = next; //перелинковка
        }
        matrix->a[row_index].next = matrix->empty; // теперь некст показывает на следующий пустой! образуется цепочка пустых эл-тов.
        matrix->empty = row_index;
        matrix->a[matrix->empty].col=-1; //на всякий случай
#ifndef NDEBUG
        DEBUG
#endif
        return 0;
    }
    matrix->a[row_index].value = value; // заменяем значение
#ifndef NDEBUG
    DEBUG
#endif
    return 0;
}

size_t matrixSize1(const Matrix *matrix) {
    return matrix->size1;
}

size_t matrixSize2(const Matrix *matrix) {
    return matrix->size2;
}

size_t matrixNonZeroCount(const Matrix *matrix) {
    return matrix->size - matrix->empty_count;
}

int matrixGet(const Matrix *matrix, size_t index1, size_t index2, long long *ptr) {
    assert((matrix->size1 == 0) == (matrix->size2 == 0) &&
        (matrix->size2 == 0 || matrix->size1 <= PTRDIFF_MAX / matrix->size2)
    );
    if (matrix->size1 <= index1 || matrix->size2 <= index2) {
        errno = EINVAL;
        return -1;
    }
    ptrdiff_t row_index = matrix->m[index1];
    while ( matrix->a && row_index != -1 && (size_t) matrix->a[row_index].col != index2 ) {
        row_index = matrix->a[row_index].next;
    }
    *ptr = row_index == -1 ? 0 : matrix->a[row_index].value;
    return 0;
}
