#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "expr_tree.h"

double exampleDict (const char * var) {
    if (strcmp(var, "a") == 0) {
        return 6;
    }
    else if (strcmp(var, "c") == 0) {
        return 7;
    }
    else if (strcmp(var, "c")) {
        return 8;
    }
    else {
        fprintf(stderr, "ERROR: Undefined variable\n");
        exit(EXIT_FAILURE);
    }
}

int main(void) {
    char *expr = "100 + (101 * 102) - 103" ;
    fprintf(stdout, expr);
    fprintf(stdout,"\n");
    fprintf(stdout, "----------------------\n");
    printPostfixFromInfix(stdout, expr);
    fprintf(stdout, "----------------------\n");
    Tree tree;
    treeCreateFromInfix(&tree, expr);
    treeInorderPrint(stdout, &tree);
    fprintf(stdout, "----------------------\n");
    double res = treeCalculate(&tree, exampleDict);
    fprintf(stdout, "Calculated: %f\n", res);
    treeDestroy(&tree);
}