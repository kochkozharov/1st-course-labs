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

bool deque_push_front(Deque* const d, const T t) {
    if (deque_is_full(d)) {
        return false;
    }
    else if (deque_is_empty(d)) {
        d->first=0;
        d->last=0;
        d->data[d->first]=t;
    }
    if (d->first==0) {
        d->first=POOL_SIZE-1;
        d->data[d->first]=t;
    }
    else {
        d->data[--(d->first)]=t;
    }
    return true;
}

bool deque_push_back(Deque* const d, const T t) {
    if (deque_is_full(d)) {
        return false;
    }
    else if (deque_is_empty(d)) {
        d->first=0;
        d->last=0;
        d->data[d->last]=t;
    }
    if (d->last==POOL_SIZE-1) {
        d->first=0;
        d->data[d->last]=t;
    }
    else d->data[++(d->last)]=t;
    return true;
}

bool deque_pop_front(Deque* const d) {
    if (deque_is_empty(d)) {
        return false;
    }
    if (deque_size(d)==1) {
        d->first=-1;
        d->last=-1;
    }
    else {
        if (d->first==POOL_SIZE-1) d->first=0;
        else d->first++;
    }
    return true;
}

bool deque_pop_back(Deque* const d) {
    if (deque_is_empty(d)) {
        return false;
    }
    if (deque_size(d)==1) {
        d->first=-1;
        d->last=-1;
    }
    else {
        if (d->last==0) d->last=POOL_SIZE-1;
        else d->last--;
    }
    return true;
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
/*
deque_iterator first(Deque* d) {

}
*/