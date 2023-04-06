#include <stdio.h>
#include "types.h"
#include "deque.h"

int main(void){
    Deque a;
    deque_create(&a);
    deque_push_back(&a, 6);

    deque_push_back(&a, 7);

    deque_push_front(&a, -1);
    deque_pop_front(&a);


    _deque_iterator i = first(&a);
    while (i.index != -1) {
        T v;
        printf("%d\n",i.index); 
        fetch(&i, &v);
        next(&i);
       // printf("%d\n", i.d->first);
        printf("%d\n",v);
        
    }
    return 0;
}