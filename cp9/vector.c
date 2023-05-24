#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include "vector.h"

static size_t newCapacity(size_t capacity);

int vectorBack(const Vector * const vector, T * const value) {
    if (vector->size == 0)
        return EINVAL;
    *value = vector->data[vector->size - 1];
    return 0;
}

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

int vectorGet(
    const Vector * const vector,
    const size_t index,
    T * const value
) {
    if (vector->size <= index)
        return EINVAL;
    *value = vector->data[index];
    return 0;
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


int vectorPopBack(Vector * const vector) {
    if (vector->size == 0)
        return EINVAL;
    --vector->size;
    return 0;
}

int vectorResize(Vector * const vector, const size_t newSize, const T value) {
    if (newSize <= vector->size) {
        vector->size = newSize;
        return 0;
    }
    assert(newSize > vector->size);
    if (newSize <= vector->capacity) {
        while (vector->size < newSize)
            vector->data[vector->size++] = value;
        return 0;
    }
    assert(newSize > vector->capacity);
    T * const data = realloc(vector->data, newSize * sizeof(T));
    if (data == NULL)
        return errno;
    vector->data = data;
    vector->capacity = newSize;
    while (vector->size < newSize)
        vector->data[vector->size++] = value;
    return 0;
}

void vectorReverse(Vector * const vector) {
    for (size_t i =0 ; i < vector->size/2; ++i) {
        T temp = vector->data[i];
        vector->data[i] = vector->data[vector->size-i-1];
        vector->data[vector->size-i-1] = temp;
    }
}

int vectorSet(Vector * const vector, const size_t index, const T value) {
    if (vector->size <= index)
        return EINVAL;
    vector->data[index] = value;
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
