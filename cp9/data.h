#ifndef DATA_H
#define DATA_H

#define KEY_SIZE (4U)

typedef struct {
    int key;
    char *value;
} Data;

int cmpData(const void* const a, const void* const b);
int cmpStrWithData(const void* const a, const void* const b);

#endif  // DATA_H
