#include <stdlib.h>
#include <errno.h>
#include <list.h>
int listCreate(List *list) {
    if (!list) {
        errno = EINVAL;
        return -1;
    }
    *list = (List) { .head = NULL, .tail = NULL, .size = 0 };
    return 0;
}

bool listIsEmpty(const List * const list) {
    if (!list) {
        errno = EINVAL;
        return -1;
    }
    return list->size == 0;
}

int listPushFront(List *list, const void * const src, const size_t size) {
    if (list == NULL || src == NULL) {
        errno = EINVAL;
        return -1;
    }
    ListNode *temp = malloc(sizeof(ListNode)+size);
    if (!temp) return -1;
    
    if (list->head == NULL) {
        temp->next = temp;
        list->head = temp;
		list->tail = temp;
    }
    else {
        temp->next = list->head;
        list->tail->next = temp;
        list->head = temp;
    }
    memcpy(temp->data, src, size);
    ++list->size;
    return 0;
}

int listPushBack(List *list, const void * const src, const size_t size) {
    if (list == NULL || src == NULL) {
        errno = EINVAL;
        return -1;
    }
    ListNode *temp = malloc(sizeof(ListNode)+size);
    if (!temp) return -1;
    
    if (list->head == NULL) {
        temp->next = temp;
        list->head = temp;
		list->tail = temp;
    }
    else  {
        temp->next = list->head;
        list->tail->next = temp;
        list->tail = temp;
    }
    memcpy(temp->data, src, size);
    ++list->size;
    return 0;
}