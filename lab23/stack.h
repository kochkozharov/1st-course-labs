#ifndef _STACK_H_
#define _STACK_H_
#include <stdbool.h>
#include <stddef.h>
#include <tree.h>

typedef tree_node stack_t;

typedef struct {
    stack_t *data;
    size_t capacity, depth;
} stack;

int stack_top(const stack *stack, stack_t *value);

size_t stack_capacity(const stack *stack);

void stack_clear(stack *stack);

void stack_create(stack *stack);

bool stack_is_empty(const stack *stack);

int stack_pop_back(stack *stack);

int stack_push_back(stack *stack, stack_t value);

int stack_resize(stack *stack, size_t newSize, stack_t value);

size_t stack_depth(const stack *stack);

void stack_destroy(stack *stack);

#endif // _STACK_H_
