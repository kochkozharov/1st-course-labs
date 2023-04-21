#include "deque.h"
#include "sort.h"

Deque* deque_concat(Deque* a, Deque* b) {
    Deque* d = deque_create(deque_length(a)+deque_length(b)+1);
    if (!d) return 0;
    while(!deque_is_empty(a)) {
        T el;
        deque_back(a, &el);
        deque_pop_back(a);
        deque_push_front(&d, el);
    }
    while(!deque_is_empty(b)) {
        T el;
        deque_front(b, &el);
        deque_pop_front(b);
        deque_push_back(&d, el);
    }
    if (a!=b){
        deque_destroy(a);
        deque_destroy(b);
    }
    else deque_destroy(a);
    return d;
}

Deque* deque_hoare_sort(Deque* d) {
    if (deque_length(d)<=1) {
        return d;
    }
    T pivot;
    deque_front(d, &pivot);
    deque_pop_front(d);
    Deque* left = deque_create(deque_capacity(d));
    Deque* right = deque_create(deque_capacity(d));
    while(!deque_is_empty(d)){
        T el;
        deque_front(d, &el);
        deque_pop_front(d);
        if (el < pivot) {
            deque_push_back(&left, el);
        }
        else {
            deque_push_back(&right, el);
        }
    }
    deque_destroy(d);
    left = deque_hoare_sort(left);
    deque_push_back(&left, pivot);
    right = deque_hoare_sort(right);
    Deque* sorted = deque_concat(left,right);
    return sorted;
}
