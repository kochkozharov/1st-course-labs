#include <assert.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "student.h"

typedef struct {
    FILE *in, *out;
} Data;

bool get(Student *const student, const void *const data) {
    FILE *const in = ((Data *)data)->in;
    const size_t count = fread(student, sizeof(Student), 1U, in);
    if (count != 1U && ferror(in) != 0) {
        perror("fread");
        exit(EXIT_FAILURE);
    } else if (count != 1U) {
        fseek(((Data *)data)->in, 0, SEEK_SET);
        return false;
    }
    return true;
}

void putStudent(const void *what, void *data) {
    const Student *st = what;
    FILE *out = ((Data *)data)->out;
    fprintf(out, "Last name: %s\n", st->lastName);
    fprintf(out, "Initials: %c%c\n", st->initials[0], st->initials[1]);
    fprintf(out, "Gender: ");
    if (st->gender == MALE)
        fprintf(out, "Male\n");
    else if (st->gender == FEMALE)
        fprintf(out, "Female\n");
    else
        fprintf(out, "N/A\n");
    fprintf(out, "Group Number: %hhu\n", st->groupNumber);
    fprintf(out, "Grades\n");
    fprintf(out, "Economics: %hhu\n", st->grades[0]);
    fprintf(out, "Philosophy: %hhu\n", st->grades[1]);
    fprintf(out, "Calculus: %hhu\n", st->grades[2]);
    fprintf(out, "Discrete Mathematics: %hhu\n", st->grades[3]);
    fprintf(out, "Linear Algebra: %hhu\n", st->grades[4]);
    fprintf(out, "Computer Science: %hhu\n", st->grades[5]);
    fprintf(out, "-----------------------------\n");
}

void putGroupInfo(const void *what, void *data) {
    const GroupInfo *res = what;
    FILE *out = ((Data *)data)->out;
    fprintf(out, "Group №%hhu: %f\n", res->groupNumber, res->maxAvg);
}

int main(const int argc, char **const argv) {
    if (argc == 2 && !strcmp(argv[1], "--help")) {
        printf("Usage: %s -f FILE [-v]\n", argv[0]);
        exit(EXIT_SUCCESS);
    }

    const char *file = NULL;
    bool displayDump = false;
    for (int opt; opt = getopt(argc, argv, "vf:"), opt != -1;) {
        switch (opt) {
            case '?':
                exit(EXIT_FAILURE);
            case 'f':
                file = optarg;
                break;
            case 'v':
                displayDump = true;
                break;
        }
    }

    FILE *in = fopen(file, "rb");
    if (in == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    Data data = {.in = in, .out = stdout};
    if (displayDump) {
        displayAll(get, putStudent, &data);
    }

    select(get, putGroupInfo, &data);

    if (fclose(in) == EOF) {
        perror("fclose");
        exit(EXIT_FAILURE);
    }

    return 0;
}
