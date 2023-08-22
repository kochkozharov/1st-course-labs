#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>

#include "expr_tree.h"

typedef char StackElem;

typedef struct {
    StackElem *data;
    size_t capacity, depth;
} Stack;

StackElem stackTop(const Stack *const stack);

int stackTopSafe(const Stack *stack, StackElem *value);

size_t stackCapacity(const Stack *stack);

void stackClear(Stack *stack);

void stackCreate(Stack *stack);

bool stackIsEmpty(const Stack *stack);

int stackPopBack(Stack *stack);

int stackPushBack(Stack *stack, StackElem value);

int stackResize(Stack *stack, size_t newSize, StackElem value);

size_t stackDepth(const Stack *stack);

void stackDestroy(Stack *stack);

#endif  // STACK_H
