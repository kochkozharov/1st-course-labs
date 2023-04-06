#ifndef _DEQUE_H_
#define _DEQUE_H_

#include <stdbool.h>
#include <stddef.h>

#include "types.h"

const int POOL_SIZE = 100;

typedef int T;

typedef struct {
    T data[POOL_SIZE];
    int first;
    int last;
} Deque;

void deque_create(Deque*);
bool deque_is_empty(const Deque*);
bool deque_is_full(const Deque*);
bool deque_push_front(Deque*, const T);
bool deque_push_back(Deque*, const T);
void deque_pop_front(Deque*);
void deque_pop_back(Deque*);
T deque_front(const Deque*);
T deque_back(const Deque*);
void deque_print(const Deque*);
size_t deque_size(const Deque*);
void deque_destroy(Deque*);

#endif