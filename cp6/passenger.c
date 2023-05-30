#include <stdbool.h>
#include <string.h>

#include "passenger.h"


void select(
    long long p,
    bool (*get)(Passenger *, const void *),
    void (*put)(const char *, const void *),
    void *data
) {
    Passenger passenger;
    while (get(&passenger, data)) {
        if ((long long) passenger.amountOfItems > p) {
            char *lastName = passenger.lastName;
            char temp[LINE_SIZE+5];
            strcpy(temp,lastName);
            size_t str_len=strlen(temp);
            temp[str_len]=' ';
            temp[str_len+1]=passenger.initials[0];
            temp[str_len+2]='.';
            temp[str_len+3]=passenger.initials[1];
            temp[str_len+4]='.';
            temp[str_len+5]='\0';
            put(temp, data);
        }
    }
}

void display(
    bool (*get)(Passenger *, const void *),
    void (*put)(const Passenger *, const void *),
    void *data
) {
    Passenger passenger;
    while (get(&passenger, data)) {
            put(&passenger, data);
    }
}

