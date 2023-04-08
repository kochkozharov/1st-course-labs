#ifndef _DEQUE_H_
#define _DEQUE_H_

#include <stdbool.h>
#include <stddef.h>

#include "types.h"

typedef int T;

typedef struct {
    int first;
    int last;
    int capacity;
    T data[];
} Deque;

typedef struct {
    const Deque* d;
    int index;
} _deque_iterator;

Deque* deque_create(const int);
bool deque_is_empty(const Deque*);
bool deque_is_full(const Deque*);
int deque_push_front(Deque*, const T);
int deque_push_back(Deque*, const T);
int deque_pop_front(Deque*);
int deque_pop_back(Deque*);
int deque_front(const Deque*, T*);
int deque_back(const Deque*, T*);
int deque_length(const Deque*);
void deque_destroy(Deque*);
int deque_resize(Deque**, int);

_deque_iterator* deque_iterator_first(const Deque*);
_deque_iterator* deque_iterator_last(const Deque*);
void deque_iterator_next(_deque_iterator**);
void deque_iterator_prev(_deque_iterator**);
int deque_iterator_fetch(const _deque_iterator*, T*);

#endif //_DEQUE_H_