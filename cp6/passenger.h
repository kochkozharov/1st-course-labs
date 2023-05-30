#ifndef PASSENGER_H
#define PASSENGER_H

#include <stdbool.h>

#define LINE_SIZE (40U)
#define FIELDS_NUMBER (8U)

typedef struct {
    char lastName[LINE_SIZE]; //40
    char initials[2]; //2
    unsigned char amountOfItems; //1 
    unsigned char totalWeightOfItems; //1
    char destination[LINE_SIZE]; //40
    char departureTime[12]; //12
    bool hasTransfers; //1
    unsigned char amountOfChildren; //1
} Passenger;

void select(
    bool (*get)(Passenger *, void *),
    void (*put)(char, void *),
    void *data
);

#endif //PASSENGER_H
