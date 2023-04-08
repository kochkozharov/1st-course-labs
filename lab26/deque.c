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

bool deque_is_empty(const Deque* const d) {
    return d->first==-1 && d->last==-1;
}

bool deque_is_full(const Deque* const d){
    return (d->first==0 && d->last==d->capacity-1) || (d->first == d->last+1);
}

int deque_length(const Deque* const d) {
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

int deque_resize(Deque** const d, int new_capacity)
{
    int len = deque_length(*d);
    if (new_capacity <= 0)
        return EINVAL;
    Deque* nd = malloc(sizeof(Deque) + new_capacity * sizeof(T));
    if (!nd) return ENOMEM;
    nd->capacity = new_capacity;
    nd->first = 0;
    nd->last = (len > new_capacity) ? new_capacity-1 : len-1;
    int r = ((*d)->capacity-(*d)->first)%(*d)->capacity;

    memcpy(nd->data,(*d)->data+(*d)->first,r * sizeof(T));
    memcpy(nd->data+r, (*d)->data, (len - r) * sizeof(T));
    free(*d);
    *d = nd;
    return 0;
}

_deque_iterator* deque_iterator_first(const Deque* const d) {
    _deque_iterator* i = malloc(sizeof(_deque_iterator));
    i->d=d;
    i->index=d->first;
    return i;
}

_deque_iterator* deque_iterator_last(const Deque* const d) {
    _deque_iterator* i = malloc(sizeof(_deque_iterator));
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

void deque_destroy(Deque* const d) {
    free(d);
}
/*
Deque* deque_concat(Deque* dst, Deque* src){

    deque_resize(&dst,dst->capacity);
    deque_resize(&src,src->capacity);
    Deque* d = malloc(sizeof(Deque)+(deque_length(dst)+deque_length(dst))*sizeof(T));
    free(src);
    free(dst);
    return d;
    //dst->last = dst->last+deque_length(src);
    //memcpy(dst->data+deque_length(dst),src->data,deque_length(src)*sizeof(T));
    //free(*src);
    
}
*/