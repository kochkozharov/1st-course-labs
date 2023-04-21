#include "stack.h"
#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

static size_t new_capacity(size_t capacity);

int stack_top(const stack * const stack, t * const value) {
    if (stack->depth == 0)
        errno = EINVAL;
        return -1;
    *value = stack->data[stack->depth - 1];
    return 0;
}

size_t stack_capacity(const stack * const stack) {
    return stack->capacity;
}

void stack_clear(stack * const stack) {
    stack->depth = 0;
}

void stack_create(stack * stack) {
    stack->data = NULL;
    stack->capacity = stack->depth = 0;
}

void stack_destroy(stack * const stack) {
    free(stack->data);
}

bool stack_is_empty(const stack * const stack) {
    return stack->depth == 0;
}

int stack_push_back(stack * const stack, const t value) {
    assert(stack->capacity >= stack->depth);
    if (stack->capacity == stack->depth) {
        const size_t capacity = new_capacity(stack->capacity);
        t * const data = realloc(stack->data, capacity * sizeof(t));
        if (data == NULL)
            return -1;
        stack->data = data;
        stack->capacity = capacity;
    }
    assert(stack->capacity > stack->depth);

    stack->data[stack->depth++] = value;
    return 0;
}


int stack_pop_back(stack * const stack) {
    if (stack->depth == 0)
        errno = EINVAL;
        return -1;
    --stack->depth;
    return 0;
}

int stack_resize(stack * const stack, const size_t newSize, const t value) {
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
    t * const data = realloc(stack->data, newSize * sizeof(t));
    if (data == NULL)
        return -1;
    stack->data = data;
    stack->capacity = newSize;
    while (stack->depth < newSize)
        stack->data[stack->depth++] = value;
    return 0;
}

size_t stack_depth(const stack * const stack) {
    return stack->depth;
}

static size_t new_capacity(const size_t capacity) {
    if (capacity == 0)
        return 1;
    return capacity <= SIZE_MAX / 2 ? capacity * 2 : SIZE_MAX;
}
