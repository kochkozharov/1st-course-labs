#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "binary_search.h"

#define SIZE (64U)
#define LIMIT (512)
#define VALUE_SIZE (16U)
#define CMP_LESS(x, y) ((x) < (y) ? -1 : (y) < (x))

typedef struct {
    int key;
    char value[VALUE_SIZE];
} Data;

static int cmpChar(const void * const a, const void * const b) {
    const char x = *(const char *) a, y = *(const char *) b;
    return CMP_LESS(x, y);
}

static int cmpData(const void * const a, const void * const b) {
    const int x = ((const Data *) a)->key, y = ((const Data *) b)->key;
    return CMP_LESS(x, y);
}

static int cmpInt(const void * const a, const void * const b) {
    const int x = *(const int *) a, y = *(const int *) b;
    return CMP_LESS(x, y);
}

void binarySearchFirst();
void binarySearchSecond();
void binarySearchLast();

int main(void) {
    binarySearchFirst();
    binarySearchSecond();
    binarySearchLast();

    return 0;
}

void binarySearchFirst() {
    char data[SIZE];
    for (size_t i = 0; i < SIZE; ++i)
        data[i] = rand() % 26 + 'a';

    qsort(data, SIZE, sizeof(char), cmpChar);
    const char key = rand() % 26 + 'a';
    const char *ptr = (char *) binarySearch(&key, data, SIZE, sizeof(char), cmpChar);

    if (ptr == NULL)
        for (size_t i = 0; i < SIZE; ++i)
            assert(data[i] != key);
    else {
        const ptrdiff_t offset = ptr - data;
        assert(offset < SIZE && *ptr == key);
    }
}

void binarySearchSecond() {
    const size_t size = rand() % SIZE + 1;
    int * const data = malloc(size * sizeof(int));
    if (data == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < size; ++i)
        data[i] = rand() % LIMIT - LIMIT / 2;

    qsort(data, size, sizeof(char), cmpInt);
    const int key = rand() % LIMIT - LIMIT / 2;
    const int *ptr = (int *) binarySearch(&key, data, size, sizeof(int), cmpInt);

    if (ptr == NULL)
        for (size_t i = 0; i < SIZE; ++i)
            assert(data[i] != key);
    else {
        const ptrdiff_t offset = ptr - data;
        assert(offset < size && *ptr == key);
    }

    free(data);
}

void binarySearchLast() {
    const size_t size = rand() % SIZE + 1;
    Data * const data = malloc(size * sizeof(Data));
    if (data == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < size; ++i) {
        data[i].key = rand() % LIMIT - LIMIT / 2;
        for (size_t j = 0; j < VALUE_SIZE - 1; ++j)
            data[i].value[j - 1] = rand() % 26 + 'a';
        data[i].value[VALUE_SIZE - 1] = '\0';
    }

    qsort(data, size, sizeof(char), cmpData);
    const int key = rand() % LIMIT - LIMIT / 2;
    const Data *ptr = (Data *) binarySearch(&key, data, size, sizeof(Data), cmpData);

    if (ptr == NULL)
        for (size_t i = 0; i < size; ++i)
            assert(data[i].key != key);
    else {
        const ptrdiff_t offset = ptr - data;
        assert(offset < size && ptr->key == key);
    }

    free(data);
}
