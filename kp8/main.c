#include <stdio.h>
#include "list.h"

int main(void) {
    List a;
    listCreate(&a, sizeof(char));

    listPushFront(&a, &(char){'j'});
    listPushFront(&a, &(char){'a'});
    listPopFront(&a);
    listPopFront(&a);
    listPopFront(&a);
    listPopFront(&a);
    listPushFront(&a, &(char){'j'});
    listPushBack(&a, &(char){'q'});
    listPushFront(&a, &(char){'w'});
    listPushBack(&a, &(char){'p'});



    for(ListIterator it = listIteratorBegin(&a), end=listIteratorEnd(&a);listIteratorNotEqual(&it, &end);listIteratorNext(&it)) {
        printf("%c\n", *(char*)listIteratorGet(&it));
    }
    printf("\n");
    ListIterator it = listIteratorBegin(&a);
    listIteratorSet(&it,&(char){'A'});
    printf("%c\n", *(char*)listIteratorGet(&it));
    listIteratorNext(&it);
    printf("%c\n", *(char*)listIteratorGet(&it));
        listIteratorNext(&it);
    printf("%c\n", *(char*)listIteratorGet(&it));
        listIteratorNext(&it);
    printf("%c\n", *(char*)listIteratorGet(&it));
        listIteratorNext(&it);
    printf("%c\n", *(char*)listIteratorGet(&it));
        listIteratorNext(&it);
    printf("%c\n", *(char*)listIteratorGet(&it));
            listIteratorNext(&it);
    if(listIteratorGet(&it)) printf("%c\n", *(char*)listIteratorGet(&it));
            listIteratorNext(&it);
    printf("%c\n", *(char*)listIteratorGet(&it));
                listIteratorNext(&it);
    printf("%c\n", *(char*)listIteratorGet(&it));
}