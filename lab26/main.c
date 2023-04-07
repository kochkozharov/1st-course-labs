#include <stdio.h>
#include "types.h"
#include "deque.h"

int main(void){
    Deque* a = deque_create(10);
    deque_push_back(a,6);

    deque_push_back(a, 7);

    deque_push_front(a, -1);
    deque_push_front(a, -1);
    deque_push_back(a, 7);
    deque_pop_back(a);

    _deque_iterator i = first(a);
    while (i.index != -1) {
        T v;
        fetch(&i, &v);
        next(&i);
        printf("%d\n",v);
        
    }

    return 0;
}