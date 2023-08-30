#include "data.h"

#include <string.h>

int cmpData(const void *const a, const void *const b) {
    const int x = (*(Data *)a).key;
    const int y = (*(Data *)b).key;
    return x - y;
}

int cmpIntWithData(const void *const int_ptr, const void *const data_ptr) {
    const int x = (*(Data *)int_ptr).key;
    const int y = (*(Data *)data_ptr).key;
    return x - y;
}
