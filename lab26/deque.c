#include <errno.h>
#include <stdlib.h>
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

bool deque_is_empty(const Deque* const d) {
    return d->first==-1 && d->last==-1;
}

bool deque_is_full(const Deque* const d){
    return (d->first==0 && d->last==d->capacity-1) || (d->first == d->last+1);
}

size_t deque_length(const Deque* const d) {
    if (deque_is_empty(d)) return 0;
    else return (d->last+1+(d->capacity - d->first)%(d->capacity));
}

int deque_push_front(Deque* const d, const T t) {
    if (deque_is_full(d)) {
        return EINVAL;
    }
    else if (deque_is_empty(d)) {
        d->first=0;
        d->last=0;
        d->data[d->first]=t;
    }
    else if (d->first==0) {
        d->first=d->capacity-1;
        d->data[d->first]=t;
    }
    else {
        d->data[--(d->first)]=t;
    }
    return 0;
}

int deque_push_back(Deque* const d, const T t) {
    if (deque_is_full(d)) {
        return EINVAL;
    }
    if (deque_is_empty(d)) {
        d->first=0;
        d->last=0;
        d->data[d->last]=t;
    }
    else if (d->last==d->capacity-1) {
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

void deque_destroy(Deque* const d) {
    d->first=d->last=-1;
}

/*
void resize(Deque* d, int new_capacity)
{
    size_t size = deque_size(d);
    if (new_capacity <= 0)
        return 0;
    if (new_capacity == d->capacity)
        return d;
    Deque *nd = malloc(sizeof(Deque) + new_capacity * sizeof(T));
    if (!nd)
        return 0;
    nd->capacity = new_capacity;
    nd->first = 0;
    nd->last = size - 1;
    int r = d->capacity - d->first;
    if (size <= r)
        memcpy(nd->data, d->data + d->first, size * sizeof(T));
    else
    {
        memcpy(nd->data, d->data + d->first, r * sizeof(T));
        memcpy(nd->data + d->capacity - d->first, d->data, (size - r) * sizeof(T));
    }
    free(d);
    *d=*nd;
}
*/
_deque_iterator first(const Deque* const d) {
    _deque_iterator i;
    i.d=d;
    i.index=d->first;
    return i;
}

_deque_iterator last(const Deque* const d) {
    _deque_iterator i;
    i.d=d;
    i.index=d->last;
    return i;
}

void next(_deque_iterator* const i) {
    if (i->index == i->d->last) i->index = -1;
    else if (++(i->index) == i->d->capacity) i->index=0;
}

void prev(_deque_iterator* const i) {
    if (i->index == i->d->first) i->index = -1;
    else if (--(i->index) == -1) i->index=i->d->capacity-1;
}

int fetch(const _deque_iterator* const i, T* const value) {
    if (i->index == -1) return EINVAL;
    *value = i->d->data[i->index];
    return 0;
}

/*
deque_iterator first(Deque* d) {

}
*/