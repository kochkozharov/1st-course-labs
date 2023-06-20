#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

#include "stack.h"

static size_t newCapacity(size_t capacity);

int stackTopSafe(const Stack * const stack, StackElem * const value) {
    if (stack->depth == 0) {
        errno = EINVAL;
        return -1;
    }
    *value = stack->data[stack->depth - 1];
    return 0;
}

StackElem stackTop(const Stack * const stack) {
    return stack->data[stack->depth - 1];
}

size_t stackCapacity(const Stack * const stack) {
    return stack->capacity;
}

void stackClear(Stack * const stack) {
    stack->depth = 0;
}

void stackCreate(Stack * stack) {
    stack->data = NULL;
    stack->capacity = stack->depth = 0;
}

void stackDestroy(Stack * const stack) {
    free(stack->data);
}

bool stackIsEmpty(const Stack * const stack) {
    return stack->depth == 0;
}

int stackPushBack(Stack * const stack, const StackElem value) {
    assert(stack->capacity >= stack->depth);
    if (stack->capacity == stack->depth) {
        const size_t capacity = newCapacity(stack->capacity);
        StackElem * const data = realloc(stack->data, capacity * sizeof(StackElem));
        if (data == NULL)
            return -1;
        stack->data = data;
        stack->capacity = capacity;
    }
    assert(stack->capacity > stack->depth);

    stack->data[stack->depth++] = value;
    return 0;
}


int stackPopBack(Stack * const stack) {
    if (stack->depth == 0) {
        errno = EINVAL;
        return -1;
    }
    --stack->depth;
    return 0;
}

int stackResize(Stack * const stack, const size_t newSize, const StackElem value) {
    if (newSize <= stack->depth) {
        stack->depth = newSize;
        return 0;
    }
    assert(newSize > stack->depth);
    if (newSize <= stack->capacity) {
        while (stack->depth < newSize)
            stack->data[stack->depth++] = value;
        return 0;
    }
    assert(newSize > stack->capacity);
    StackElem * const data = realloc(stack->data, newSize * sizeof(StackElem));
    if (data == NULL)
        return -1;
    stack->data = data;
    stack->capacity = newSize;
    while (stack->depth < newSize)
        stack->data[stack->depth++] = value;
    return 0;
}

size_t stackDepth(const Stack * const stack) {
    return stack->depth;
}

static size_t newCapacity(const size_t capacity) {
    if (capacity == 0)
        return 1;
    return capacity <= SIZE_MAX / 2 ? capacity * 2 : SIZE_MAX;
}
