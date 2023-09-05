#include "student.h"

#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define MAX_GROUPS UCHAR_MAX
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

typedef struct {
    unsigned int sum;
    unsigned int amount;
} _el;

void select(
    bool (*get)(Student *, const void *),
    void (*put)(const void *, void *),
    void *data) {
    Student student;
    _el arr[MAX_GROUPS];
    for (int i = 0; i < MAX_GROUPS; ++i)
        arr[i].sum = arr[i].amount = 0;
    while (get(&student, data))
        if (student.gender == FEMALE) {
            unsigned char grp = student.groupNumber - 1;
            unsigned int sum = 0;
            for (int i = 0; i < EXAMS_COUNT; ++i)
                sum += student.grades[i];
            arr[grp].sum += sum;
            arr[grp].amount++;
        }
    double avgs[MAX_GROUPS] = {0};
    double mostMaxAvg = -1;
    for (int i = 0; i < MAX_GROUPS; ++i) {
        if (arr[i].amount != 0) {
            double avg = (double)arr[i].sum / (double)arr[i].amount / EXAMS_COUNT;
            avgs[i] = avg;
            mostMaxAvg = MAX(avg, mostMaxAvg);
        }
    }
    if (mostMaxAvg == -1) return;
    for (int i = 0; i < MAX_GROUPS; ++i) {
        if (avgs[i] == mostMaxAvg) {
            GroupInfo info = {.groupNumber = i + 1, .maxAvg = mostMaxAvg};
            put(&info, data);
        }
    }
}

void displayAll(
    bool (*get)(Student *, const void *),
    void (*put)(const void *, void *),
    void *data) {
    Student student;
    while (get(&student, data))
        put(&student, data);
}