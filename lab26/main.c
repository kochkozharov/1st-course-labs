#include <stdio.h>

#include "types.h"
#include "deque.h"

int main(void){
    Deque a;
    deque_create(&a);
    printf("%zu\n",sizeof(Deque));
    deque_push_back(&a, 6);
    deque_push_back(&a, 7);
    deque_push_front(&a, -1);
    int front;
    deque_front(&a, &front);
    printf("%d\n",front);
    return 0;
}