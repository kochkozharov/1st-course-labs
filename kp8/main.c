#include <stdio.h>
#include "list.h"

int main(void) {
    List a;
    listCreate(&a, sizeof(char));
    listPushFront(&a, &(char){'G'});
    listPushFront(&a, &(char){'a'});
    listPushFront(&a, &(char){'j'});
    listPushBack(&a, &(char){'q'});
    listPushFront(&a, &(char){'w'});
    listPushBack(&a, &(char){'p'});
    for(ListIterator it = listIteratorBegin(&a), end=listIteratorEnd(&a);listIteratorNotEqual(&it, &end);listIteratorNext(&it)) {
        PRINT_LIST_ITERATOR("%c\n", char, it);
    }
    printf("reverse:\n");
    listReverse(&a);
    for(ListIterator it = listIteratorBegin(&a), end=listIteratorEnd(&a);listIteratorNotEqual(&it, &end);listIteratorNext(&it)) {
        PRINT_LIST_ITERATOR("%c\n", char, it);
    }
    printf("back and front\n");
    printf("%c\n",*(char*)listFront(&a));
    printf("%c\n",*(char*)listBack(&a));
    printf("work with iterators\n");
    ListIterator it = listIteratorBegin(&a);
    listIteratorSet(&it,&(char){'A'});
    PRINT_LIST_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    listInsertAfter(&it,&(char){'Q'});
    PRINT_LIST_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    PRINT_LIST_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    PRINT_LIST_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    listInsertAfter(&it,&(char){'K'});
    PRINT_LIST_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    listEraseAfter(&it);
    PRINT_LIST_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    PRINT_LIST_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    PRINT_LIST_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    PRINT_LIST_ITERATOR("%c\n", char, it);
    listDestroy(&a);
}
