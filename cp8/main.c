#include <stdio.h>
#include "list.h"

int main(void) {
    List a;
    listCreate(&a, sizeof(char));
    listPushFront(&a, &(char){'G'});
    printf("push front G\n");
    listPushFront(&a, &(char){'a'});
    printf("push front a\n");
    listPushFront(&a, &(char){'j'});
    printf("push front j\n");
    listPushBack(&a, &(char){'q'});
    printf("push back q\n");
    listPushFront(&a, &(char){'w'});
    printf("push front w\n");
    listPushBack(&a, &(char){'p'});
    printf("push back p\n");
    for(ListIterator it = listIteratorBegin(&a), end=listIteratorEnd(&a);listIteratorNotEqual(&it, &end);listIteratorNext(&it)) {
        PRINT_LIST_ITERATOR("%c\n", char, it);
    }
    printf("-----------------\n");
    printf("reverse:\n");
    listReverse(&a);
    for(ListIterator it = listIteratorBegin(&a), end=listIteratorEnd(&a);listIteratorNotEqual(&it, &end);listIteratorNext(&it)) {
        PRINT_LIST_ITERATOR("%c\n", char, it);
    }
    printf("-----------------\n");
    printf("back and front\n");
    printf("%c\n",*(char*)listFront(&a));
    printf("%c\n",*(char*)listBack(&a));
    printf("-----------------\n");
    printf("work with iterators\n");
    ListIterator it = listIteratorBegin(&a);
    printf("created iterator pointing to 1st node\n");
    PRINT_LIST_ITERATOR("%c\n", char, it);
    listIteratorSet(&it,&(char){'A'});
    printf("node pointed by iterator value is set to A\n");
    listIteratorNext(&it);
    printf("iterator pointing to the next node\n");
    PRINT_LIST_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    printf("iterator pointing to the next node\n");
    PRINT_LIST_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    printf("iterator pointing to the next node\n");
    PRINT_LIST_ITERATOR("%c\n", char, it);
    listInsertAfter(&it,&(char){'K'});
    printf("inserted K after iterator\n");
    listIteratorNext(&it);
    printf("iterator pointing to the next node\n");
    PRINT_LIST_ITERATOR("%c\n", char, it);
    listEraseAfter(&it);
    printf("erased node after iterator\n");
    listIteratorNext(&it);
    printf("iterator pointing to the next node\n");
    PRINT_LIST_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    printf("iterator pointing to the next node\n");
    PRINT_LIST_ITERATOR("%c\n", char, it);
    listIteratorNext(&it);
    printf("iterator pointing to the next node\n");
    PRINT_LIST_ITERATOR("%c\n", char, it);
    printf("-----------------\n");
    printf("result\n");
    for(ListIterator it = listIteratorBegin(&a), end=listIteratorEnd(&a);listIteratorNotEqual(&it, &end);listIteratorNext(&it)) {
        PRINT_LIST_ITERATOR("%c\n", char, it);
    }
    listDestroy(&a);
}
