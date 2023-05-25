#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include "vector.h"

static size_t newCapacity(size_t capacity);

size_t vectorCapacity(const Vector * const vector) {
    return vector->capacity;
}

void vectorCreate(Vector * vector) {
    vector->data = NULL;
    vector->capacity = vector->size = 0;
}

T *vectorData(const Vector * const vector) {
    return vector->data;
}

void vectorDestroy(Vector * const vector) {
    for (size_t i=0; i<vector->size;++i){
        free(vector->data[i]);
    }
    free(vector->data);
}

bool vectorIsEmpty(const Vector * const vector) {
    return vector->size == 0;
}

int vectorPushBack(Vector * const vector, const T value) {
    assert(vector->capacity >= vector->size);
    if (vector->capacity == vector->size) {
        const size_t capacity = newCapacity(vector->capacity);
        T * const data = realloc(vector->data, capacity * sizeof(T));
        if (data == NULL)
            return errno;
        vector->data = data;
        vector->capacity = capacity;
    }
    assert(vector->capacity > vector->size);

    vector->data[vector->size++] = value;
    return 0;
}

size_t vectorSize(const Vector * const vector) {
    return vector->size;
}

static size_t newCapacity(const size_t capacity) {
    if (capacity == 0)
        return 1;
    return capacity <= SIZE_MAX / 2 ? capacity * 2 : SIZE_MAX;
}
