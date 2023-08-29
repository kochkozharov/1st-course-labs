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

size_t vectorCapacity(const Vector *vector);

void vectorCreate(Vector *vector);

T *vectorData(const Vector *vector);

bool vectorIsEmpty(const Vector *vector);

int vectorPushBack(Vector *vector, T value);

size_t vectorSize(const Vector *vector);

void vectorDestroy(Vector *vector);

#endif  // VECTOR_H
