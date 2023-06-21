#include <stdio.h>

#include "expr_tree.h"

int main(void) {
    printPostfixFromInfix("100 + (101 * 102 - 103");
    Tree tree;
    treeCreateFromInfix(&tree, "100 + (101 * 102 - 103");
    treeInorderPrint(&tree, stdout);
    treeDestroy(&tree);
}

