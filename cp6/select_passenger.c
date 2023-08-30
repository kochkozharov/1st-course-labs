#include <assert.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "passenger.h"

typedef struct {
    FILE *in, *out;
} Data;

bool get(Passenger *const passenger, const void *const data) {
    FILE *const in = ((Data *)data)->in;
    const size_t count = fread(passenger, sizeof(Passenger), 1U, in);
    if (count != 1U && ferror(in) != 0) {
        perror("fread");
        exit(EXIT_FAILURE);
    } else if (count != 1U) {
        fseek(((Data *)data)->in, 0, SEEK_SET);
        return false;
    }
    return true;
}

void putName(const Passenger *const passenger, const void *const data) {
    FILE *const out = ((Data *)data)->out;
    char name[LINE_SIZE + 5];
    strcpy(name, passenger->lastName);
    size_t str_len = strlen(name);
    name[str_len] = ' ';
    name[str_len + 1] = passenger->initials[0];
    name[str_len + 2] = '.';
    name[str_len + 3] = passenger->initials[1];
    name[str_len + 4] = '.';
    name[str_len + 5] = '\0';
    fprintf(out, "passengerName = %s\n", name);
}

void putPassenger(const Passenger *const passenger, const void *const data) {
    FILE *const out = ((Data *)data)->out;
    fprintf(out, "lastName = %s\n", passenger->lastName);
    fprintf(out, "initials = %c%c\n", passenger->initials[0], passenger->initials[1]);
    fprintf(out, "amountOfItems = %hhu\n", passenger->amountOfItems);
    fprintf(out, "totalWeightOfItems = %hhu\n", passenger->totalWeightOfItems);
    fprintf(out, "destination = %s\n", passenger->destination);
    const char *dt = passenger->departureTime;
    fprintf(out, "departureTime = %c%c.%c%c.%c%c%c%c %c%c:%c%c\n", dt[0], dt[1], dt[2], dt[3], dt[4], dt[5], dt[6], dt[7], dt[8], dt[9], dt[10], dt[11]);
    if (passenger->hasTransfers)
        fprintf(out, "hasTransfers = true\n");
    else
        fprintf(out, "hasTransfers = false\n");
    fprintf(out, "amountOfChildren = %hhu\n", passenger->amountOfChildren);
    fprintf(out, "----------------------------------\n");
}

int main(const int argc, char **const argv) {
    if (argc == 2 && !strcmp(argv[1], "--help")) {
        printf("Usage: %s -f FILE -p PARAMETER [-v]\n", argv[0]);
        exit(EXIT_SUCCESS);
    }

    const char *file = NULL;
    long long parameter = 0;
    bool displayDump = false;
    bool hasParam = false;
    for (int opt; opt = getopt(argc, argv, "vf:p:"), opt != -1;) {
        switch (opt) {
            case '?':
                exit(EXIT_FAILURE);
            case 'f':
                file = optarg;
                break;
            case 'p':;
                char *end;
                parameter = strtoll(optarg, &end, 10);
                hasParam = true;
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
        select(-1, get, putPassenger, &data);
    }
    if (hasParam)
        select(parameter, get, putName, &data);

    if (fclose(in) == EOF) {
        perror("fclose");
        exit(EXIT_FAILURE);
    }

    return 0;
}
