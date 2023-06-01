#include <stdbool.h>
#include <string.h>

#include "passenger.h"


void select(
    long long p,
    bool (*get)(Passenger *, const void *),
    void (*put)(const Passenger *, const void *),
    void *data
) {
    Passenger passenger;
    while (get(&passenger, data)) {
        if ((long long) passenger.amountOfItems > p) {
            put(&passenger, data);
        }
    }
}


