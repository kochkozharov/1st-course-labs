#include <stdio.h>
#include "list.h"

int main(void) {
    List a;
    double n = 0.4;
    listCreate(&a, sizeof(double));
    listPushFront(&a, &n);
    listPushFront(&a, &n);
    listPushFront(&a, &n);
    listPushFront(&a, &(double){1});
    listPushFront(&a, &n);
    listPushBack(&a, &(double){3.1});
    listPushBack(&a, &(double){3.2});
    listPushFront(&a, &n);
    listPushBack(&a, &(double){3.32});
    listPushFront(&a, &(double){1});
    listPushBack(&a, &(double){3.32});


    for(ListIterator it = listIteratorBegin(&a), end=listIteratorEnd(&a);listIteratorNotEqual(&it, &end);listIteratorNext(&it)) {
        printf("%f\n", *(double*)listIteratorGet(&it));
    }
}