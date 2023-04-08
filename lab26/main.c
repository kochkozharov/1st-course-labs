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
    deque_pop_front(a);
    deque_push_front(a,3);
    deque_resize(&a,a->capacity);
    for (_deque_iterator* i = deque_iterator_first(a);i;deque_iterator_next(&i)) {
        T v;
        deque_iterator_fetch(i, &v);
        printf("%d ",v);
    }
    printf("\n");
    printf("-------------\n");
    Deque* b = deque_create(5);
    deque_push_back(b,6);
    deque_push_front(b,6);
    deque_resize(&b, 3);
    printf("%d \n",b->last);
    for (_deque_iterator* i = deque_iterator_first(b);i;deque_iterator_next(&i)) {
        T v;
        deque_iterator_fetch(i, &v);
        printf("%d ",v);
    }
    printf("\n");
    deque_resize(&b, 2);
    printf("%d \n",b->last);
    for (_deque_iterator* i = deque_iterator_first(b);i;deque_iterator_next(&i)) {
        T v;
        deque_iterator_fetch(i, &v);
        printf("%d ",v);
    }
    printf("\n");
    printf("-------------\n");
    Deque* c = deque_concat(a,b);
    for (_deque_iterator* i = deque_iterator_first(c);i;deque_iterator_next(&i)) {
        T v;
        deque_iterator_fetch(i, &v);
        printf("%d ",v);
    }
    printf("\n");
    //deque_concat(a,b);
    /*
    for (_deque_iterator* i = deque_iterator_first(a);i;deque_iterator_next(&i)) {
        T v;
        deque_iterator_fetch(i, &v);
        printf("%d ",v);
    }
    */
    return 0;
}