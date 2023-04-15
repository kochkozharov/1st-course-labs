#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include "types.h"
#include "stack.h"

static size_t new_capacity(size_t capacity);

int stack_back(const stack * const stack, t * const value) {
    if (stack->size == 0)
        return EINVAL;
    *value = stack->data[stack->size - 1];
    return 0;
}

size_t stack_capacity(const stack * const stack) {
    return stack->capacity;
}

void stack_clear(stack * const stack) {
    stack->size = 0;
}

void stack_create(stack * stack) {
    stack->data = NULL;
    stack->capacity = stack->size = 0;
}

t *stack_data(const stack * const stack) {
    return stack->data;
}

void stack_destroy(stack * const stack) {
    free(stack->data);
}

bool stack_is_empty(const stack * const stack) {
    return stack->size == 0;
}

int stack_push_back(stack * const stack, const t value) {
    assert(stack->capacity >= stack->size);
    if (stack->capacity == stack->size) {
        const size_t capacity = new_capacity(stack->capacity);
        t * const data = realloc(stack->data, capacity * sizeof(t));
        if (data == NULL)
            return errno;
        stack->data = data;
        stack->capacity = capacity;
    }
    assert(stack->capacity > stack->size);

    stack->data[stack->size++] = value;
    return 0;
}


int stack_pop_back(stack * const stack) {
    if (stack->size == 0)
        return EINVAL;
    --stack->size;
    return 0;
}

int stack_resize(stack * const stack, const size_t newSize, const t value) {
    if (newSize <= stack->size) {
        stack->size = newSize;
        return 0;
    }
    assert(newSize > stack->size);
    if (newSize <= stack->capacity) {
        while (stack->size < newSize)
            stack->data[stack->size++] = value;
        return 0;
    }
    assert(newSize > stack->capacity);
    t * const data = realloc(stack->data, newSize * sizeof(t));
    if (data == NULL)
        return errno;
    stack->data = data;
    stack->capacity = newSize;
    while (stack->size < newSize)
        stack->data[stack->size++] = value;
    return 0;
}

size_t stack_size(const stack * const stack) {
    return stack->size;
}

static size_t new_capacity(const size_t capacity) {
    if (capacity == 0)
        return 1;
    return capacity <= SIZE_MAX / 2 ? capacity * 2 : SIZE_MAX;
}
