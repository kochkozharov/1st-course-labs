#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
        if (key_len==0) {
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
    mergeSort(table, lines_count, sizeof(Data), cmpData);
    printf("-------------------------------------\n");
    for (size_t i = 0; i < lines_count; ++i)
        printf("%-4d %s\n", table[i].key, table[i].value);
    printf("-------------------------------------\n");
    /*
    printf("---------\n");
#if (1)  // 1 is stable, 0 is unstable but faster in some cases
#else
    int asc = 1, desc = 1;
    for (size_t i = 0; (asc == 1 || desc == 1) && i < lines_count - 1; ++i) {
        if (cmpData(&table[i], &table[i + 1]) < 0)
            desc = 0;
        else if (cmpData(&table[i], &table[i + 1]) > 0)
            asc = 0;
    }

    if (desc) {
        reverse(table, lines_count, sizeof(Data *));
    } else if (asc == 0 && desc == 0) {
        mergeSort(table, lines_count, sizeof(Data *), cmpData);
    }
#endif

    for (size_t i = 0; i < lines_count; ++i) {
        printf("%s %s\n", table[i].key, table[i].value);
    }
    printf("---------\n");
    */
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
