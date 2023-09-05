#ifndef PASSENGER_H
#define PASSENGER_H

#include <stdbool.h>

#define LINE_SIZE (40U)
#define EXAMS_COUNT (6)

typedef enum {
    MALE,
    FEMALE
} Gender;

typedef struct {
    char lastName[LINE_SIZE];   // 40
    char initials[2];           // 2
    Gender gender;              // 1
    unsigned char groupNumber;  // 1
    unsigned char grades[EXAMS_COUNT];
} Student;

typedef struct {
    unsigned char groupNumber;
    double maxAvg;
} GroupInfo;
/*
typedef struct {
        unsigned char economics;
        unsigned char philosophy;
        unsigned char calculus;
        unsigned char discreteMathematics;
        unsigned char linearAlgebra;
        unsigned char computerScience;
} Grades; */

void select(
    bool (*get)(Student *, const void *),
    void (*put)(const void *, void *),
    void *data);

void displayAll(
    bool (*get)(Student *, const void *),
    void (*put)(const void *, void *),
    void *data);

#endif  // PASSENGER_H
