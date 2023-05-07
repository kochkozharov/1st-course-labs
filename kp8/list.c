#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "list.h"

int listCreate(List *list) { //create terminator
    if (!list) {
        exit(EXIT_FAILURE);
    }
    list->head = malloc(sizeof(ListNode)+sizeof(ListNode*));
    if (!list->head) return -1;
    list->head->next=list->head;
    memcpy(list->head->data,&(list->head), sizeof(ListNode*)); //head->prev=head only for terminator
    ++list->size;
    return 0;
}

bool listIsEmpty(const List * const list) {
    if (!list) {
        exit(EXIT_FAILURE);
    }
    return list->size == 0;    
}

size_t listSize(const List *list) {
    return list->size;
}

int listPushFront(List *list, const void * const src, const size_t size) {
    if (list == NULL || src == NULL) {
        exit(EXIT_FAILURE);
    }
    ListNode *temp = malloc(sizeof(ListNode)+size);
    if (!temp) return -1;
    memcpy(temp->data, src, size);
    temp->next = list->head->next;
    list->head->next = temp;
    ++list->size;
    return 0;
}

int listPushBack(List *list, const void * const src, const size_t size) {
    if (list == NULL || src == NULL) {
        exit(EXIT_FAILURE); 
    }
    ListNode *temp = malloc(sizeof(ListNode)+size);
    if (!temp) return -1;
    temp->next = list->head;
    ListNode *last_node;
    memcpy(&last_node, list->head->data, sizeof(ListNode *));
    last_node->next=temp;
    memcpy(list->head->data,&temp, sizeof(ListNode*)); 
    memcpy(temp->data, src, size);
    ++list->size;
    return 0;
}

ListIterator listIteratorBegin(List *list) {
    return (ListIterator) { .node=list->head->next };
}

ListIterator listIteratorEnd(List *list) {
    return (ListIterator) { .node=list->head };
}

ListIterator *ListIteratorNext(ListIterator *it) {
    if (it == NULL)
	{
		exit(EXIT_FAILURE);
	}
	it->node = it->node->next;
}