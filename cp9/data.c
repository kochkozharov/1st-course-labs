#include "data.h"

#include <string.h>

int cmpData(const void *const a, const void *const b) {
    const char *x = (*(Data **)a)->key;
    const char *y = (*(Data **)b)->key;
    return strcmp(x, y);
}

int cmpStrWithData(const void *const a, const void *const b) {
    const char *x = (*(char **)a);
    const char *y = (*(Data **)b)->key;
    return strcmp(x, y);
}
