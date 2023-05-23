#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>
#include "data.h"

typedef Data *T;

typedef struct {
    T *data;
    size_t capacity, size;
} Vector;

int vectorBack(const Vector *vector, T *value);

size_t vectorCapacity(const Vector *vector);

void vectorClear(Vector *vector);

void vectorCreate(Vector *vector);

T *vectorData(const Vector *vector);

int vectorGet(const Vector *vector, size_t index, T *value);

bool vectorIsEmpty(const Vector *vector);

int vectorPopBack(Vector *vector);

int vectorPushBack(Vector *vector, T value);

int vectorResize(Vector *vector, size_t newSize, T value);

int vectorSet(Vector *vector, size_t index, T value);

size_t vectorSize(const Vector *vector);

void vectorDestroy(Vector *vector);

#endif // VECTOR_H
