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
    int front;
    deque_front(&a, &front);
    printf("%d\n",front);
    printf("%zu\n", deque_size(&a));
    deque_clear(&a);
    printf("%d\n", deque_front(&a, &front));
    printf("%d\n", front);
    return 0;
}