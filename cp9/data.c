#include <string.h>
#include "data.h"

int cmpData(const Data * const a, const Data * const b) {
    const char *x = a->key;
    const char *y = b->key;
    return strcmp(x,y);
}
