#include <stddef.h>

#include "binary_search.h"

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

void *binarySearch(
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
            return (void *) ptr;
    }
    return NULL;
}

/*
Обязательно: equal_range, lower_bound, upper_bound
Карма +1: сортирока бинарным деревом (АВЛ)
*/
