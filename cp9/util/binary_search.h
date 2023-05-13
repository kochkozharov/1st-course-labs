#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <stddef.h>

void *binarySearch(
    const void *key,
    const void *data,
    size_t length,
    size_t size,
    int (*compare)(const void *, const void *)
);

#endif // BINARY_SEARCH_H
