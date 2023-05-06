#ifndef _LIST_H_
#define _LIST_H_
#include <stdbool.h>
#include <stddef.h>

typedef struct ListNode {
    ListNode *next, *prev;
    char data[];
} ListNode;


typedef struct {
    ListNode *head, *tail;
    size_t size;
} List;

typedef struct {

} List;

typedef struct  {
    ListNode *head;
} ListIterator;


int listBack(const List *list, void *value);

void listClear(List *list);

void listCreate(List *list);

bool listIsEmpty(const List *list);

ListIterator listIteratorBegin(List *list);

ListIterator listIteratorEnd(List *list);

int listIteratorInsert(List *list, ListIterator *listIterator, void *value);

int listIteratorRemove(List *list, ListIterator *listIterator);

ListIterator listIteratorNext(const ListIterator *listIterator);

ListIterator listIteratorPrev(const ListIterator *listIterator);

int listIteratorGet(const ListIterator *listIterator, void *value);

int listIteratorSet(ListIterator *listIterator, void *value);

int listPopBack(List *list);

int listPopFront(List *list);

int listPushBack(List *list, void *value);

int listPushFront(List *list, void *value);

size_t listSize(const List *list);

void listDestroy(List *list);

#endif //_LIST_H_