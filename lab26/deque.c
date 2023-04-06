#include <errno.h>

#include "deque.h"

void deque_create(Deque* const d) {
    d->first=-1;
    d->last=-1;
}

bool deque_is_empty(const Deque* const d) {
    return d->first==-1 && d->last==-1;
}

bool deque_is_full(const Deque* const d){
    return (d->first==0 && d->last==POOL_SIZE-1) || (d->first == d->last+1);
}

size_t deque_size(const Deque* const d) {
    if (deque_is_empty(d)) return 0;
    else return (d->last+1+(POOL_SIZE - d->first)%POOL_SIZE);
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
        d->first=POOL_SIZE-1;
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
    else if (d->last==POOL_SIZE-1) {
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
    if (deque_size(d)==1) {
        d->first=-1;
        d->last=-1;
    }
    else if (d->first==POOL_SIZE-1) d->first=0;
    else d->first++;
    return 0;
}

int deque_pop_back(Deque* const d) {
    if (deque_is_empty(d)) {
        return EINVAL;
    }
    if (deque_size(d)==1) {
        d->first=-1;
        d->last=-1;
    }
    else {
        if (d->last==0) d->last=POOL_SIZE-1;
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

void deque_clear(Deque* const d) {
    d->first=d->last=-1;
}

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
    else if (++(i->index) == POOL_SIZE) i->index=0;
}

void prev(_deque_iterator* const i) {
    if (i->index == i->d->first) i->index = -1;
    else if (--(i->index) == -1) i->index=POOL_SIZE-1;
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