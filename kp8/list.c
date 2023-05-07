#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

int listCreate(List * const list, size_t data_size) { //create terminator
    list->head = malloc(sizeof(ListNode)+sizeof(ListNode*));
    if (!list->head) return -1;
    list->head->next=list->head;
    memcpy(list->head->data,&(list->head), sizeof(ListNode*)); //head->prev=head only for terminator
    list->data_size = data_size;
    list->count=0;
    return 0;
}

bool listIsEmpty(const List * const list) {
    return list->count == 0;    
}

size_t listSize(const List * const list) {
    return list->count;
}

int listPushFront(List * const list, const void * const src) {
    ListNode *temp = malloc(sizeof(ListNode)+list->data_size);
    if (!temp) return -1;
    memcpy(temp->data, src, list->data_size);
    if (list->count == 0) memcpy(list->head->data,&temp,sizeof(ListNode*));
    temp->next = list->head->next;
    list->head->next = temp;
    ++list->count;
    return 0;
}

int listPushBack(List * const list, const void * const src) {
    ListNode *temp = malloc(sizeof(ListNode)+list->data_size);
    if (!temp) return -1;
    temp->next = list->head;
    ListNode *last_node;
    memcpy(&last_node, list->head->data, sizeof(ListNode *));
    last_node->next=temp;
    memcpy(list->head->data,&temp, sizeof(ListNode*)); 
    memcpy(temp->data, src, list->data_size);
    ++list->count;
    return 0;
}



ListIterator listIteratorBegin(const List * const list) {
    return (ListIterator) { .node = list->head->next, .list = (List *) list};
}

ListIterator listIteratorEnd(const List * const list) {
    return (ListIterator) { .node=list->head, .list = (List *) list};
}

ListIterator *listIteratorNext(ListIterator *it) {
	it->node = it->node->next;
    return it;
}

void *listIteratorGet(const ListIterator * const  it) {
    if (it->node == it->list->head) {
        errno = EINVAL;
        return NULL;
    }
    void *out = malloc(it->list->data_size);
    memcpy(out, it->node->data, it->list->data_size);
    return out;
}

int listIteratorSet(ListIterator * const  it, const void * const src) { //unsafe, break list when set value of terminator
    if (it->node == it->list->head) {
        errno = EINVAL;
        return -1;
    }
    memcpy(it->node->data, src, it->list->data_size);
    return 0;
}

bool listIteratorEqual(const ListIterator *it1, const ListIterator *it2) {
    return it1->node == it2->node;
}

bool listIteratorNotEqual(const ListIterator *it1, const ListIterator *it2) {
    return it1->node != it2->node;
}
