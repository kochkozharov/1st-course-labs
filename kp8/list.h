#ifndef _LIST_H_
#define _LIST_H_
#include <stdbool.h>
#include <stddef.h>

typedef struct ListNode {
    struct ListNode *next;
    char data[];
} ListNode;

typedef struct {
    ListNode *head;
    size_t data_size;
    size_t count;
} List;

typedef struct  {
    ListNode *node;
    size_t data_size;
} ListIterator;

void *listFront(const List *list);

void *listBack(const List *list);

void listClear(List *list);

int listCreate(List *list, size_t data_size);

bool listIsEmpty(const List *list);

ListIterator listIteratorBegin(const List *list);

ListIterator listIteratorEnd(const List *list);

int listInsertAfter(List *list, ListIterator *listIterator, void *value);

void listErase(List *list, ListIterator *listIterator);

ListIterator *listIteratorNext(ListIterator *listIterator);

void *listIteratorGet(const ListIterator *listIterator);

int listIteratorSet(ListIterator *listIterator, size_t size);

bool listIteratorEqual(const ListIterator *it1, const ListIterator *it2);

bool listIteratorNotEqual(const ListIterator *it1, const ListIterator *it2);

void listPopFront(List *list);

void listPopBack(List *list);

int listPushFront(List *list, const void *src);

int listPushBack(List *list, const void *src);

size_t listSize(const List *list);

void listDestroy(List *list);

void listReverse(List *list);

#endif //_LIST_H_