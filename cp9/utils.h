#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    void *first;
    void *second;
} Pair;

bool simpleBinarySearch(
    const void *const key,
    const void *data,
    size_t length,
    const size_t size,
    int (*const compare)(const void *, const void *));

void *binarySearch(const void *key, const void *data, size_t length,
                   size_t size, int (*compare)(const void *, const void *));

void *lowerBound(const void *const key, const void *array, size_t length,
                 const size_t size,
                 int (*const compare)(const void *, const void *));

void *upperBound(const void *const key, const void *array, size_t length,
                 const size_t size,
                 int (*const compare)(const void *, const void *));

int mergeSort(void *a, const size_t count, const size_t size,
              int (*comp)(const void *, const void *));

void reverse(const void *array, size_t length, const size_t size);

Pair equalRange(const void *const key, const void *array, size_t length,
                const size_t size,
                int (*const compare)(const void *, const void *));

#endif  // UTILS_H
