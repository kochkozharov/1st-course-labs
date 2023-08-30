#include <ctype.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "data.h"
#include "string.h"
#include "utils.h"
#include "vector.h"

#define STR_INT_LEN (12U)

static char *inputString(FILE *fp) {
    size_t size = 16;
    char *str;
    int ch;
    size_t len = 0;
    str = malloc(size);
    if (!str) return str;
    while ((ch = fgetc(fp)) != '\n' && ch != EOF) {
        str[len++] = ch;
        if (len == size) {
            str = realloc(str, size *= 2);
            if (!str) return str;
        }
    }
    str[len++] = '\0';
    return realloc(str, len);
}

int main(void) {
    FILE *table_txt = fopen("table.txt", "r");
    if (!table_txt) {
        fprintf(stderr, "Cannot open file.\n");
        exit(EXIT_FAILURE);
    }
    Vector vtable;
    vectorCreate(&vtable);

    for (;;) {
        Data line;
        char key_str[STR_INT_LEN];
        int ch;
        size_t key_len = 0;
        while ((ch = fgetc(table_txt)) != ';') {
            if ((ch == ' ' || ch == '0' || ch == '\n') && key_len == 0) continue;
            if (ch == EOF && key_len == 0) goto esc;
            if (ch == EOF || !(isdigit(ch) || ch == '+' || ch == '-') || ch == '\n' || key_len == STR_INT_LEN) {
                fprintf(stderr, "Invalid key.\n");
                exit(EXIT_FAILURE);
            }
            key_str[key_len++] = ch;
        }
        if (key_len == 0) {
            fprintf(stderr, "Invalid key.\n");
            exit(EXIT_FAILURE);
        }
        key_str[key_len] = '\0';
        long res = strtol(key_str, NULL, 10);
        if (res > INT_MAX) {
            fprintf(stderr, "Integer overflow.\n");
            exit(EXIT_FAILURE);
        }
        if (res < INT_MIN) {
            fprintf(stderr, "Integer overflow.\n");
            exit(EXIT_FAILURE);
        }
        line.key = res;
        if (!(line.value = inputString(table_txt)))
            abort();
        vectorPushBack(&vtable, line);
    }
esc:
    if (fclose(table_txt)) {
        fprintf(stderr, "Cannot close file.\n");
        exit(EXIT_FAILURE);
    };
    Data *table = vectorData(&vtable);
    size_t lines_count = vectorSize(&vtable);
    for (size_t i = 0; i < lines_count; ++i)
        printf("%-4d %s\n", table[i].key, table[i].value);
    if (!mergeSort(table, lines_count, sizeof(Data), cmpData)) abort();
    printf("-------------------------------------\n");
    for (size_t i = 0; i < lines_count; ++i)
        printf("%-4d %s\n", table[i].key, table[i].value);
    printf("-------------------------------------\n");
    for (;;) {
        char *str = inputString(stdin);
        if (feof(stdin)) {
            free(str);
            break;
        };
        char *endptr;
        long num = strtol(str, &endptr, 10);
        if (*endptr != '\0') {
            fprintf(stderr, "Bad request.\n");
            exit(EXIT_FAILURE);
        }
        free(str);
        Data *res = binarySearch(&num, table, lines_count, sizeof(Data),
                                 cmpIntWithData);
        if (!res)
            printf("N/A\n");
        else {
            Data *end = table + lines_count;
            while (res != end && cmpIntWithData(&num, res) == 0) {
                printf("%-4d %s\n", res->key, res->value);
                ++res;
            }
        }
    }
    vectorDestroy(&vtable);
    return 0;
}
