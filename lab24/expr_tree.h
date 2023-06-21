#ifndef EXPR_TREE_H
#define EXPR_TREE_H

#include <stddef.h>
#include <stdio.h>

#define VARIABLE_LENGTH (16U)
#define NODES_LENGTH (512U)

typedef struct Node Node;

typedef struct {
    Node *left, *right;
    char opChar;
} Operator;

typedef union {
    Operator op;
    char variable[VARIABLE_LENGTH];
    double value;
} NodeUnion;

typedef enum {
    OPERATOR,
    VALUE,
    VARIABLE
} NodeType;

struct Node {
    Node *parent;
    NodeUnion nodeUnion;
    NodeType nodeType;
};

typedef struct {
    Node *root;
} Tree;

void printPostfixFromInfix(FILE *file, const char *expr);

void treeCreateFromInfix(Tree * const tree, const char *expr);

void treeDestroy(Tree * const tree);

void treeInorderPrint(FILE *file, Tree * const tree);

void tree_transform(Tree * const tree);

#endif //EXPR_TREE_H
