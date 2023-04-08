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
    for (_deque_iterator* i = deque_iterator_first(a);i;deque_iterator_next(&i)) {
        T v;
        deque_iterator_fetch(i, &v);
        printf("%d ",v);
    }
    printf("\n");
    printf("-------------\n");
    deque_resize(&a,5);
    deque_pop_front(a);
    deque_push_front(a,3);
    for (_deque_iterator* i = deque_iterator_first(a);i;deque_iterator_next(&i)) {
        T v;
        deque_iterator_fetch(i, &v);
        printf("%d ",v);
    }
    printf("\n");
    return 0;
}