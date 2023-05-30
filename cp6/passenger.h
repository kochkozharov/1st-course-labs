#ifndef PASSENGER_H
#define PASSENGER_H

#include <stdbool.h>

#define LINE_SIZE (40U)
#define FIELDS_NUMBER (8U)

typedef struct {
    char lastName[LINE_SIZE];
    char initials[2];
    unsigned char amountOfItems;
    unsigned char totalWeightOfItems;
    char destination[LINE_SIZE]; 
    char departureTime[12]; //???
    bool hasTransfers;
    unsigned char amountOfChildren;
} Passenger;

void select(
    bool (*get)(Passenger *, void *),
    void (*put)(char, void *),
    void *data
);

#endif //PASSENGER_H
