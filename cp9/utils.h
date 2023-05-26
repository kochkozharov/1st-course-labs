#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

typedef struct {
    void *first;
    void *second;
} Pair;

void *binarySearch(
    const void *key,
    const void *data,
    size_t length,
    size_t size,
    int (*compare)(const void *, const void *)
);

void *lowerBound(
    const void * const key,
    const void *array,
    size_t length,
    const size_t size,
    int (* const compare)(const void *, const void *)
);

void *upperBound(
    const void * const key,
    const void *array,
    size_t length,
    const size_t size,
    int (* const compare)(const void *, const void *)
);

void mergeSort(
    void *a, 
    size_t count,
    size_t size, 
    int (*comp) (const void *, const void *)
);

void reverse(
    const void *array,
    size_t length,
    const size_t size
);

Pair equalRange(
    const void * const key,
    const void *array,
    size_t length,
    const size_t size,
    int (* const compare)(const void *, const void *)
);

#endif // UTILS_H
