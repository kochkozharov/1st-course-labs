#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "list.h"

int listCreate(List * const list, const size_t data_size) { //create terminator
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

int listPopFront(List * const list) {
    if (list->count == 0) {
        errno = EINVAL;
        return -1;
    }
    else if (list->count == 1) {
        free(list->head->next);
        list->head->next=list->head;
        memcpy(list->head->data,&(list->head), sizeof(ListNode*));
    }
    else {
        ListNode *temp = list->head->next->next;
        free(list->head->next);
        list->head->next = temp;
    }
    --list->count;
    return 0;
}

//int listPopBack(List *list); cannot be O(1) in singly-linked list...

ListIterator listIteratorBegin(const List * const list) {
    return (ListIterator) { .node = list->head->next, .list = (List *) list};
}

ListIterator listIteratorEnd(const List * const list) {
    return (ListIterator) { .node=list->head, .list = (List *) list};
}

ListIterator *listIteratorNext(ListIterator * const it) {
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

int listIteratorSet(ListIterator * const  it, const void * const src) { 
    if (it->node == it->list->head) {
        errno = EINVAL;
        return -1;
    }
    memcpy(it->node->data, src, it->list->data_size);
    return 0;
}

bool listIteratorEqual(const ListIterator * const it1, const ListIterator * const it2) {
    return it1->node == it2->node;
}

bool listIteratorNotEqual(const ListIterator * const it1, const ListIterator * const it2) {
    return it1->node != it2->node;
}

int listInsertAfter(ListIterator * const it, const void * const src) {
    ListNode *temp = malloc(sizeof(ListNode)+it->list->data_size);
    if (!temp) return -1;
    if (it->node->next == it->list->head) { //pushBack copy paste
        temp->next = it->list->head;
        ListNode *last_node;
        memcpy(&last_node, it->list->head->data, sizeof(ListNode *));
        last_node->next=temp;
        memcpy(it->list->head->data,&temp, sizeof(ListNode*)); 
    }
    else {
        temp->next = it->node->next;
        it->node->next = temp;
    }
    memcpy(temp->data, src, it->list->data_size);
    ++it->list->count;
    return 0;
}

int listEraseAfter(ListIterator * const it) {
    if (it->node->next == it->list->head) {
        errno = EINVAL;
        return -1;
    }
    if (it->node->next->next == it->list->head) {
        memcpy(it->list->head->data,&it->node, sizeof(ListNode*)); 
    }
    ListNode *temp = it->node->next;
    it->node->next = temp->next;
    free(temp);
    --it->list->count;
    return 0;
}

void listDestroy(List * const list) {
    ListNode *node = list->head->next;
    while (node != list->head) {
        ListNode *temp=node->next;
        free(node);
        node = temp;
    }
    free(node);
    list->count=0;
    list->data_size=0;
    list->head=NULL;
}

void listClear(List * const list) {
    ListNode *node = list->head->next;
    while (node != list->head) {
        ListNode *temp=node->next;
        free(node);
        node = temp;
    }
    list->head=node;
    memcpy(list->head->data,&(list->head), sizeof(ListNode*));
    list->head->next=list->head;
    list->count=0;
}

void *listFront(const List * const list) {
    if (list->count ==0) return NULL;
    return list->head->next->data;
}

void *listBack(const List * const list) {
    if (list->count ==0) return NULL;
    ListNode *last_node;
    memcpy(&last_node, list->head->data, sizeof(ListNode *));
    return last_node->data;
}

void listReverse(List * const list) {
    if (list->count <= 1) return;
    ListNode *temp=list->head->next;
    ListNode *prev=list->head;
    ListNode *last_node;
    memcpy(&last_node, list->head->data, sizeof(ListNode *));
    memcpy(list->head->data, &list->head->next,sizeof(ListNode *));
    list->head->next=last_node;
    while (temp !=list->head) {
        ListNode *temp2=temp->next;
        temp->next=prev;
        prev=temp;
        temp=temp2;
    }
}