#include <stdio.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "passenger.h"

typedef struct {
    FILE *in, *out;
} Data;


bool get(Passenger * const passenger, void * const data) {
    FILE * const in = ((Data *) data)->in;
    const size_t count = fread(passenger, sizeof(Passenger), 1U, in);
    if (count != 1U && ferror(in) != 0) {
        perror("fread");
        exit(EXIT_FAILURE);
    } else if (count != 1U)
        return false;
    return true;
}

void put(const char *lastName, const void * data) {
    FILE * const out = ((Data *) data)->out;
    fprintf(out, "lastName = %s\n", lastName);
}

int main(const int argc, char ** const argv) {
    if (!strcmp(argv[1], "--help")) {
        printf("Usage: %s -f FILE -p PARAMETER\n", argv[0]);
        exit(EXIT_SUCCESS);
    }
    else if (argc != 5) {
        fprintf(stderr, "%s: wrong count of arguments\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *file = NULL;
    long long parameter = 0;
    for (int opt; opt = getopt(argc, argv, "f:p:"), opt != -1; ) {
        switch (opt) {
            case ':':
                fprintf(stderr, "%s: unknown option -- %c\n", argv[0], optopt);
                break;
            case '?':
                break;
            case 'f':
                file = optarg;
                break;
            case 'p': ;
                char *end;
                parameter = strtoll(optarg, &end, 10);
                break;
            default:
                assert(false);
        }
    }

    printf("file: %s, parameter: %lld\n", file, parameter);

    FILE *in = fopen(file, "rb");
    if (in == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    Data data = { .in = in, .out = stdout };
    select(parameter, get, put, &data);

    if (fclose(in) == EOF) {
        perror("fclose");
        exit(EXIT_FAILURE);
    }

    return 0;
}
