#include <stdio.h>

#include "expr_tree.h"

int main(void) {
    char *expr = "(0 + 1) * (2 - 3)" ;
    fprintf(stdout, expr);
    fprintf(stdout,"\n");
    printPostfixFromInfix(stdout, expr);

    Tree tree;
    treeCreateFromInfix(&tree, expr);
    treeInorderPrint(stdout, &tree);
    treeDestroy(&tree);
}