#include <stdio.h>
#include "types.h"
#include "deque.h"

int main(void){
    Deque* a = deque_create(4);
    deque_push_back(a,6);
    deque_push_back(a, 7);
    deque_push_front(a, -1);
    deque_push_front(a, -1);
    deque_push_back(a, 7);
    _deque_iterator i = deque_iterator_first(a);
    while (i.index != -1) {
        T v;
        deque_iterator_fetch(&i, &v);
        deque_iterator_next(&i);
        printf("%d\n",v);
    }
    printf("---\n");
    deque_resize(&a,5);
    deque_push_front(a,3);

    i = deque_iterator_first(a);
    while (i.index != -1) {
        T v;
        deque_iterator_fetch(&i, &v);
        deque_iterator_next(&i);
        printf("%d\n",v);
    }
    return 0;
}