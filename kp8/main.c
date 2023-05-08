#include <stdio.h>
#include "list.h"
int main(void) {
    List a;
    listCreate(&a, sizeof(char));
    listPushFront(&a, &(char){'j'});
    listPushFront(&a, &(char){'a'});
    listPushFront(&a, &(char){'j'});
    listPushBack(&a, &(char){'q'});
    listPushFront(&a, &(char){'w'});
    listPushBack(&a, &(char){'p'});
    listPopFront(&a);
    for(ListIterator it = listIteratorBegin(&a), end=listIteratorEnd(&a);listIteratorNotEqual(&it, &end);listIteratorNext(&it)) {
        PRINT_ITERATOR("%c\n", char, it);
    }
    printf("\n");
    ListIterator it = listIteratorBegin(&a);
    listIteratorSet(&it,&(char){'A'});
    PRINT_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    listInsertAfter(&it,&(char){'Q'});
    PRINT_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    PRINT_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    PRINT_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    listInsertAfter(&it,&(char){'K'});
    PRINT_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    listEraseAfter(&it);
    PRINT_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    PRINT_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    PRINT_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    PRINT_ITERATOR("%c\n", char, it);
}