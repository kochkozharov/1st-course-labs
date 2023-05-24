#include <string.h>
#include "data.h"

int cmpData(const void * const a, const void * const b) {
    const char *x = (*(Data**)a)->key;
    const char *y = (*(Data**)b)->key;
    return strcmp(x,y);
}
