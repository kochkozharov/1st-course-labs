#ifndef _STACK_H_
#define _STACK_H_

#include <stdbool.h>
#include <stddef.h>

#include "types.h"

typedef struct {
    t *data;
    size_t capacity, size;
} stack;

int stack_back(const stack *stack, t *value);

size_t stack_capacity(const stack *stack);

void stack_clear(stack *stack);

void stack_create(stack *stack);

t *stac_data(const stack *stack);

bool stack_is_empty(const stack *stack);

int stack_pop_back(stack *stack);

int stack_push_back(stack *stack, t value);

int stack_resize(stack *stack, size_t newSize, t value);

size_t stack_size(const stack *stack);

void stack_destroy(stack *stack);

#endif // _STACK_H_