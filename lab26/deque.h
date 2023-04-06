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
    const Deque* d;
    int index;
} _deque_iterator;

void deque_create(Deque*);
bool deque_is_empty(const Deque*);
bool deque_is_full(const Deque*);
int deque_push_front(Deque*, const T);
int deque_push_back(Deque*, const T);
int deque_pop_front(Deque*);
int deque_pop_back(Deque*);
int deque_front(const Deque*, T*);
int deque_back(const Deque*, T*);
size_t deque_size(const Deque*);
void deque_clear(Deque*);

_deque_iterator first(const Deque*);
_deque_iterator last(const Deque*);
void next(_deque_iterator*);
void prev(_deque_iterator*);
int fetch(const _deque_iterator*, T*);

#endif //_DEQUE_H_