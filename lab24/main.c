#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expr_tree.h"

double exampleDict(const char *var) {
    if (strcmp(var, "a") == 0) {
        return 0;
    } else if (strcmp(var, "b") == 0) {
        return 7;
    } else if (strcmp(var, "c") == 0) {
        return 8;
    } else {
        fprintf(stderr, "ERROR: Undefined variable\n");
        exit(EXIT_FAILURE);
    }
}

static char *inputString(FILE *fp) {
    size_t size = 16;
    char *str;
    int ch;
    size_t len = 0;
    str = malloc(size);
    if (!str) return str;
    while ((ch = fgetc(fp)) != '\n') {
        if (ch == EOF) {
            if (len == 0) {
                free(str);
                return NULL;
            } else
                break;
        };
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
    fprintf(stdout, "Enter expression: ");
    char *expr = inputString(stdin);
    if (!expr) abort();
    fprintf(stdout, "%s\n", expr);
    fprintf(stdout, "----------------------\n");
    fprintf(stdout, "Postfix form\n");
    printPostfixFromInfix(stdout, expr);
    fprintf(stdout, "----------------------\n");
    Tree tree;
    treeCreateFromInfix(&tree, expr);
    free(expr);
    fprintf(stdout, "Expression tree\n");
    treeInorderPrint(stdout, &tree);
    fprintf(stdout, "----------------------\n");
    double res = treeCalculate(&tree, exampleDict);
    fprintf(stdout, "Calculated: %f\n", res);
    fprintf(stdout, "----------------------\n");
    fprintf(stdout, "Transformation:\n");
    treeTransform(&tree, exampleDict);
    treeInorderPrint(stdout, &tree);
    fprintf(stdout, "----------------------\n");
    res = treeCalculate(&tree, exampleDict);
    fprintf(stdout, "Calculated: %f\n", res);
    treeDestroy(&tree);
}
