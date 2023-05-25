#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

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
/*
Обязательно: equal_range, lower_bound, upper_bound
Карма +1: сортирока бинарным деревом (АВЛ)
*/
