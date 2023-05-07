#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

int listCreate(List * const list, size_t data_size) { //create terminator
    if (!list) {
        exit(EXIT_FAILURE);
    }
    list->head = malloc(sizeof(ListNode)+sizeof(ListNode*));
    if (!list->head) return -1;
    list->head->next=list->head;
    memcpy(list->head->data,&(list->head), sizeof(ListNode*)); //head->prev=head only for terminator
    list->data_size = data_size;
    list->count=0;
    return 0;
}

bool listIsEmpty(const List * const list) {
    if (!list) {
        exit(EXIT_FAILURE);
    }
    return list->count == 0;    
}

size_t listSize(const List * const list) {
    return list->count;
}

int listPushFront(List * const list, const void * const src) {
    if (list == NULL || src == NULL) {
        exit(EXIT_FAILURE);
    }
    ListNode *temp = malloc(sizeof(ListNode)+list->data_size);
    if (!temp) return -1;
    memcpy(temp->data, src, list->data_size);
    if (list->count == 0) {memcpy(list->head->data,&temp,sizeof(ListNode*));
    printf("yes");
    }
    temp->next = list->head->next;
    list->head->next = temp;
    ++list->count;
    return 0;
}

int listPushBack(List * const list, const void * const src) {
    if (list == NULL || src == NULL) {
        exit(EXIT_FAILURE); 
    }
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
    if (list == NULL)
	{
		exit(EXIT_FAILURE);
	}
    return (ListIterator) { .node = list->head->next, .data_size = list->data_size};
}

ListIterator listIteratorEnd(const List * const list) {
    if (list == NULL)
	{
		exit(EXIT_FAILURE);
	}
    return (ListIterator) { .node=list->head };
}

ListIterator *listIteratorNext(ListIterator *it) {
    if (it == NULL)
	{
		exit(EXIT_FAILURE);
	}
	it->node = it->node->next;
    return it;
}

void *listIteratorGet(const ListIterator * const  it) {
    if (it == NULL)
	{
		exit(EXIT_FAILURE);
	}
    void *out = malloc(it->data_size);
    memcpy(out, it->node->data, it->data_size);
    return out;
}

bool listIteratorEqual(const ListIterator *it1, const ListIterator *it2) {
    return it1->node == it2->node;
}

bool listIteratorNotEqual(const ListIterator *it1, const ListIterator *it2) {
    return it1->node != it2->node;
}