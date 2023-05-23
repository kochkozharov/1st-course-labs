#ifndef DATA_H
#define DATA_H

#define KEY_SIZE (6U)

typedef struct {
    char key[KEY_SIZE];
    char value[];
} Data;

int cmpData(const Data * const a, const Data * const b);

#endif //DATA_H
