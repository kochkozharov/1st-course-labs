#include "data.h"

#include <string.h>

int cmpData(const void *const a, const void *const b) {
    const int x = (*(Data *)a).key;
    const int y = (*(Data *)b).key;
    return x < y;
}

int cmpIntWithData(int n, const void *const ptr) {
    const int y = (*(Data *)ptr).key;
    return n < y;
}
