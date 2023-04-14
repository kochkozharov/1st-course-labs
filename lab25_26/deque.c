#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "deque.h"

Deque* deque_create(const int capacity)
{
    if (capacity <= 0)
        return 0;
    Deque *d = malloc(sizeof(Deque) + capacity * sizeof(T));
    if (d)
    {
        d->capacity = capacity;
        d->first = d->last = -1;
    }
    return d;
}

size_t deque_length(const Deque* const d) {
    if (d->first <= d->last) {
        return d->last - d->first+1;
    }
    else {
        return d->last + 1 + d->capacity-d->first;
    }
}

size_t deque_capacity(const Deque* d) {
    return d->capacity;
}

bool deque_is_empty(const Deque* const d) {
    return d->first==-1 && d->last==-1;
}

bool deque_is_full(const Deque* const d){
    return (d->first==0 && d->last==d->capacity-1) || (d->first == d->last+1);
}

int deque_push_front(Deque** const ptr_d, const T t) {
    Deque* d = *ptr_d;
    if (deque_is_empty(d)) {
        d->first=0;
        d->last=0;
        d->data[d->first]=t;
        return 0;
    }
    if (deque_is_full(d)) {
        *ptr_d=deque_resize(d,(d->capacity)*2);
    }
    d = *ptr_d;
    if (d->first==0) {
        d->first=d->capacity-1;
        d->data[d->first]=t;
    }
    else {
        d->data[--(d->first)]=t;
    }
    return 0;
}

int deque_push_back(Deque** const ptr_d, const T t) {
    Deque* d = *ptr_d;
    if (deque_is_empty(d)) {
        d->first=0;
        d->last=0;
        d->data[d->last]=t;
        return 0;
    }
    if (deque_is_full(d)) {
        *ptr_d=deque_resize(d,(d->capacity)*2);
    }
    d = *ptr_d;
    if (d->last==d->capacity-1) {
        d->last=0;
        d->data[d->last]=t;
    }
    else d->data[++(d->last)]=t;
    return 0;
}

int deque_pop_front(Deque* const d) {
    if (deque_is_empty(d)) {
        return EINVAL;
    }
    if (deque_length(d)==1) {
        d->first=-1;
        d->last=-1;
    }
    else if (d->first==d->capacity-1) d->first=0;
    else d->first++;
    return 0;
}

int deque_pop_back(Deque* const d) {
    if (deque_is_empty(d)) {
        return EINVAL;
    }
    if (deque_length(d)==1) {
        d->first=-1;
        d->last=-1;
    }
    else {
        if (d->last==0) d->last=d->capacity-1;
        else d->last--;
    }
    return 0;
}

int deque_front(const Deque* const d, T* const value) {
    if(deque_is_empty(d)) {
        return EINVAL;
    }
    *value = d->data[d->first];
    return 0;    
}

int deque_back(const Deque* const d, T* const value) {
    if(deque_is_empty(d)) {
        return EINVAL;
    }
    *value = d->data[d->last];
    return 0;    
}

Deque* deque_resize(Deque* const d, int new_capacity)
{
    int len = deque_length(d);
    if (new_capacity <= 0)
        return NULL;
    Deque* nd = malloc(sizeof(Deque) + new_capacity * sizeof(T));
    if (!nd) return NULL;
    nd->capacity = new_capacity;
    nd->first = 0;
    nd->last = (len > new_capacity) ? new_capacity-1 : len-1;

    int r = (d)->capacity-(d)->first; //?
    if (len <= r)  memcpy(nd->data, (d)->data + (d)->first, len * sizeof(T));
    else {
        memcpy(nd->data,(d)->data+(d)->first,r * sizeof(T));
        memcpy(nd->data+r, (d)->data, (len - r) * sizeof(T));
    }
    free(d);
    return nd;
}

void deque_destroy(Deque* const d) {
    free(d);
}

_deque_iterator* deque_iterator_first(const Deque* const d) {
    _deque_iterator* i = malloc(sizeof(_deque_iterator));
    if (!i) return 0;
    i->d=d;
    i->index=d->first;
    return i;
}

_deque_iterator* deque_iterator_last(const Deque* const d) {
    _deque_iterator* i = malloc(sizeof(_deque_iterator));
    if (!i) return 0;
    i->d=d;
    i->index=d->last;
    return i;
}

void deque_iterator_next(_deque_iterator** const i) {
    if ((*i)->index == (*i)->d->last) {free(*i);*i=0;}
    else if (++((*i)->index) == (*i)->d->capacity) (*i)->index=0;
}

void deque_iterator_prev( _deque_iterator** const i) {
    if ((*i)->index == (*i)->d->first) {free(*i);*i=0;}
    else if (--((*i)->index) == -1) (*i)->index=(*i)->d->capacity-1;
}

int deque_iterator_fetch(const _deque_iterator* const i, T* const value) {
    if (i->index == -1) return EINVAL;
    *value = i->d->data[i->index];
    return 0;
}
// 3 -1 6 7 6
//     3
// -1    3 6 7 6
//  *       3
//             3 6 7 6
//                3
//                  3 6 7 6
//                 ...

// 3 -1 6 7 6
//     3
// -1    6 7 6 3
//  *       6
//        3    6  7  6 
//        *       6
//                   6 7 6
//                 ...
