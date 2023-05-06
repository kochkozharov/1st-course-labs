#ifndef _LIST_H_
#define _LIST_H_
#include <stdbool.h>
#include <stddef.h>

typedef struct ListNode {
    ListNode *next;
    char data[];
} ListNode;

typedef struct {
    ListNode *head;
    ListNode *tail; //for fast push_back
    size_t size;
} List;

typedef struct  {
    ListNode *ptr;
} ListIterator;

void *listFront(const List *list);

void listClear(List *list);

int listCreate(List *list);

bool listIsEmpty(const List *list);

ListIterator listIteratorBeforeBegin(List *list);

ListIterator listIteratorBegin(List *list);

ListIterator listIteratorEnd(List *list);

int listInsertAfter(List *list, ListIterator *listIterator, void *value);

int listErase(List *list, ListIterator *listIterator);

ListIterator listIteratorNext(const ListIterator *listIterator);

int listIteratorGet(const ListIterator *listIterator);

void listIteratorSet(ListIterator *listIterator);

int listPopFront(List *list);

int listPushFront(List *list, const void *src, const size_t size);

int listPushBack(List *list, const void *src, const size_t size);

size_t listSize(const List *list);

void listDestroy(List *list);

#endif //_LIST_H_