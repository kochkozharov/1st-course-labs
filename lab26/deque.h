#ifndef _DEQUE_H_
#define _DEQUE_H_

#include <stdbool.h>
#include <stddef.h>

#include "types.h"

#define POOL_SIZE 100

typedef int T;

typedef struct {
    T data[POOL_SIZE];
    int first;
    int last;
} Deque;

typedef struct {
    Deque* d;
    int index;
} deque_iterator;

void deque_create(Deque*);
bool deque_is_empty(const Deque*);
bool deque_is_full(const Deque*);
bool deque_push_front(Deque*, const T);
bool deque_push_back(Deque*, const T);
bool deque_pop_front(Deque*);
bool deque_pop_back(Deque*);
int deque_front(const Deque*, T*);
int deque_back(const Deque*, T*);
void deque_print(const Deque*);
size_t deque_size(const Deque*);

deque_iterator fisrt(const Deque*);
deque_iterator last(const Deque*);
deque_iterator next(deque_iterator*);
deque_iterator prev(deque_iterator*);
T fetch(const deque_iterator*) ;

#endif