#include <stdio.h>
#include "types.h"
#include "deque.h"
#include "sort.h"

int main(void){
    printf("Deque create and push\n");
    Deque* a = deque_create(4);
    deque_push_back(&a,6);
    deque_push_back(&a, 7);
    deque_push_front(&a, -1);
    deque_push_front(&a, -1);
    deque_push_back(&a, 7);
    for (_deque_iterator* i = deque_iterator_first(a);i;deque_iterator_next(&i)) {
        T v;
        deque_iterator_fetch(i, &v);
        printf("%d ",v);
    }
    printf("\n");
    printf("-------------\n");
    printf("Deque pop\n");
    deque_pop_front(a);
    for (_deque_iterator* i = deque_iterator_first(a);i;deque_iterator_next(&i)) {
        T v;
        deque_iterator_fetch(i, &v);
        printf("%d ",v);
    }
    printf("\n");
    printf("-------------\n");
    printf("Deque resize\n");
    Deque* b = deque_create(5);
    deque_push_back(&b,6);
    deque_push_front(&b,6);
    printf("Capacity: %ld\n",deque_capacity(b));
    for (_deque_iterator* i = deque_iterator_first(b);i;deque_iterator_next(&i)) {
        T v;
        deque_iterator_fetch(i, &v);
        printf("%d ",v);
    }
    printf("\n");
    b=deque_resize(b, 1);
    printf("Capacity: %ld\n",deque_capacity(b));
    for (_deque_iterator* i = deque_iterator_first(b);i;deque_iterator_next(&i)) {
        T v;
        deque_iterator_fetch(i, &v);
        printf("%d ",v);
    }
    printf("\n");
    printf("-------------\n");
    printf("Deque cocncat previous deques\n");
    Deque* c = deque_concat(a,b);
    for (_deque_iterator* i = deque_iterator_first(c);i;deque_iterator_next(&i)) {
        T v;
        deque_iterator_fetch(i, &v);
        printf("%d ",v);
    }
    printf("\n");
    printf("-------------\n");
    printf("Deque sort\n");
    Deque* d = deque_hoare_sort(c);
    for (_deque_iterator* i = deque_iterator_first(d);i;deque_iterator_next(&i)) {
        T v;
        deque_iterator_fetch(i, &v);
        printf("%d ",v);
    }
    printf("\n");
    printf("-------------\n");
    printf("Deque another one sort\n");
    Deque* g = deque_create(10);
    deque_push_back(&g,2);
    deque_push_back(&g,2);
    deque_push_front(&g,-2);
    deque_push_back(&g,3);
    deque_push_front(&g,6);
    for (_deque_iterator* i = deque_iterator_first(g);i;deque_iterator_next(&i)) {
        T v;
        deque_iterator_fetch(i, &v);
        printf("%d ",v);
    }
    printf("\n");

    Deque* q = deque_hoare_sort(g);
        for (_deque_iterator* i = deque_iterator_first(q);i;deque_iterator_next(&i)) {
        T v;
        deque_iterator_fetch(i, &v);
        printf("%d ",v);
    }
    printf("\n");
    return 0;
}