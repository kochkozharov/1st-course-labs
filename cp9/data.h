#ifndef DATA_H
#define DATA_H

#define KEY_SIZE (4U)

typedef struct {
    int key;
    char *value;
} Data;

int cmpData(const void* const a, const void* const b);
int cmpIntWithData(const void *const int_ptr, const void *const data_ptr);

#endif  // DATA_H
