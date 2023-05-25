#ifndef DATA_H
#define DATA_H

#define KEY_SIZE (6U)

typedef struct {
    char key[KEY_SIZE];
    char value[];
} Data;

int cmpData(const void * const a, const void * const b);
int cmpKeyWithData(const void * const a, const void * const b);

#endif //DATA_H
