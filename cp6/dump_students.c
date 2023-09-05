#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "student.h"

int readStudent(Student *st) {
    printf("Last name: ");
    if (scanf("%39s", st->lastName) != 1) goto err;
    if (getchar() != '\n') goto err;
    printf("Initials: ");
    if (scanf("%c%c", &st->initials[0], &st->initials[1]) != 2) goto err;
    if (st->initials[1] != '\n' && getchar() != '\n') goto err;
    printf("Gender (m/f): ");
    unsigned char ans;
    scanf("%c", &ans);
    if (getchar() != '\n') goto err;
    if (ans == 'm')
        st->gender = MALE;
    else if (ans == 'f')
        st->gender = FEMALE;
    else
        goto err;
    printf("Group number: ");
    scanf("%hhu", &st->groupNumber);
    printf("Grades\n");
    if (getchar() != '\n') goto err;
    printf("Economics: ");
    scanf("%hhu", &st->grades[0]);
    if (getchar() != '\n') goto err;
    printf("Philosophy: ");
    scanf("%hhu", &st->grades[1]);
    if (getchar() != '\n') goto err;
    printf("Calculus: ");
    scanf("%hhu", &st->grades[2]);
    if (getchar() != '\n') goto err;
    printf("Discrete Mathematics: ");
    scanf("%hhu", &st->grades[3]);
    if (getchar() != '\n') goto err;
    printf("Linear Algebra: ");
    scanf("%hhu", &st->grades[4]);
    if (getchar() != '\n') goto err;
    printf("Computer Science: ");
    scanf("%hhu", &st->grades[5]);
    if (getchar() != '\n') goto err;

    printf("Passenger successfully dumped!\n");
    return 0;
err:
    errno = EINVAL;
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: program filename\n");
        exit(EXIT_SUCCESS);
    }
    Student st;
    FILE *out = fopen(argv[1], "ab");
    if (!out) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    if (readStudent(&st) == 0)
        fwrite(&st, sizeof(st), 1, out);
    else {
        perror("readStudent");
        exit(EXIT_FAILURE);
    }
    if (fclose(out) == EOF) {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
    return 0;
}
