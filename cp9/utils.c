#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

static inline void *ptrOffset(
    const void * const ptr,
    const ptrdiff_t idx,
    const size_t size
) {
    return (char *) ptr + idx * size;
}

static inline void *ptrIncrement(
    const void * const ptr,
    const size_t size
) {
    return ptrOffset(ptr, 1, size);
}

static inline void *elemAt(
    const void * const ptr,
    const size_t idx,
    const size_t size
) {
    return ptrOffset(ptr, (ptrdiff_t) idx, size);
}
/*
bool binarySearch(
    const void * const key,
    const void *data,
    size_t length,
    const size_t size,
    int (* const compare)(const void *, const void *)
) {
    while (length != 0) {
        const size_t middle = length >> 1;
        const void * const ptr = elemAt(data, middle, size);
        const int cmp = compare(key, ptr);
        if (cmp < 0)
            length = middle;
        else if (cmp > 0) {
            data = ptrIncrement(ptr, size);
            length -= middle + 1;
        } else
            return true;
    }
    return false;
}
*/
void *binarySearch(
    const void * const key,
    const void *array,
    size_t length,
    const size_t size,
    int (* const compare)(const void *, const void *)
) {
    void *end=elemAt(array,length,size);
    while (length != 0U) {
        const size_t index = length >> 1U;
        void * const middle = elemAt(array, index, size);
        const int result = compare(key, middle);
        if (result <= 0)
            length = index;
        else {
            array = ptrIncrement(middle, size);
            length -= index + 1U;
        }
    }
    if (array!=end && compare(key,array)==0) return (void*)array;
    return NULL;
}

void reverse(
    const void *array,
    size_t length,
    const size_t size
) {
    for (size_t i = 0 ; i < length>>1; ++i) {
        void *temp = malloc(size);
        memcpy(temp,elemAt(array, i, size),size);
        memcpy(elemAt(array, i, size),elemAt(array, length-i-1, size),size);
        memcpy(elemAt(array, length-i-1, size),temp,size);
        free(temp);
    }
}

void *lowerBound(
    const void * const key,
    const void *array,
    size_t length,
    const size_t size,
    int (* const compare)(const void *, const void *)
) {
    while (length != 0U) {
        const size_t index = length >> 1U;
        void * const middle = elemAt(array, index, size);
        const int result = compare(key, middle);
        if (result <= 0)
            length = index;
        else {
            array = ptrIncrement(middle, size);
            length -= index + 1U;
        }
    }
    return (void *) array;
}

static void merge(
    void *a,
    size_t left,
    size_t mid,
    size_t right,
    size_t size,
    int (* const comp)(const void *, const void *)
) {
    size_t it1=0;
    size_t it2=0;
    void *result[right-left];

    while (left+it1 < mid && mid+it2 < right) {
        if (comp(elemAt(a,left+it1,size),elemAt(a,mid+it2,size))<0) {
            memcpy(elemAt(result,it1+it2,size),elemAt(a,left+it1,size),size);
            ++it1;
        }
        else {
            memcpy(elemAt(result,it1+it2,size),elemAt(a,mid+it2,size),size);
            ++it2;
        }
    }
    while (left+it1<mid) {
        memcpy(elemAt(result,it1+it2,size),elemAt(a,left+it1,size),size);
        ++it1;
    }
    while (mid+it2<right) {
        memcpy(elemAt(result,it1+it2,size),elemAt(a,mid+it2,size),size);
        ++it2;
    }
    for (size_t i = 0; i < it1+it2; ++i) {
        memcpy(elemAt(a,left+i,size),elemAt(result,i,size),size);
    }
}

void mergeSort(
    void *a,
    size_t count,
    size_t size, 
    int (*comp) (const void *, const void *)
) {
    for (size_t i = 1; i < count; i*=2) {
        for (size_t j = 0; j < count-i; j += 2*i) {
            merge(a,j,j+i, MIN(j+2*i, count),size,comp);
        }
    }
}
/*
Обязательно: equal_range, lower_bound, upper_bound
Карма +1: сортирока бинарным деревом (АВЛ)
*/
