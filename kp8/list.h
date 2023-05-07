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
    size_t size;
} List;

typedef struct  {
    ListNode *node;
} ListIterator;

void *listFront(const List *list);

void *listBack(const List *list);

void listClear(List *list);

int listCreate(List *list);

bool listIsEmpty(const List *list);

ListIterator listIteratorBegin(List *list);

ListIterator listIteratorEnd(List *list);

int listInsertAfter(List *list, ListIterator *listIterator, void *value);

void listErase(List *list, ListIterator *listIterator);

void listIteratorNext(const ListIterator *listIterator);

void *listIteratorGet(const ListIterator *listIterator);

int listIteratorSet(ListIterator *listIterator);

bool listIteratorEqual(const ListIterator *it1, const ListIterator *it2);

bool listIteratorNotEqual(const ListIterator *it1, const ListIterator *it2);

void listPopFront(List *list);

void listPopBack(List *list);

int listPushFront(List *list, const void *src, const size_t size);

int listPushBack(List *list, const void *src, const size_t size);

size_t listSize(const List *list);

void listDestroy(List *list);

void listReverse(List *list);
#endif //_LIST_H_