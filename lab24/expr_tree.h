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

typedef enum { OPERATOR, VALUE, VARIABLE } NodeType;

struct Node {
    //Node *parent;
    NodeUnion nodeUnion;
    NodeType nodeType;
};

typedef struct {
    Node *root;
} Tree;

void printPostfixFromInfix(FILE *file, const char *expr);

void treeCreateFromInfix(Tree *tree, const char *expr);

void treeDestroy(Tree *tree);

void treeInorderPrint(FILE *file, const Tree *tree);

double treeCalculate(const Tree *tree, double (*dict)(const char *));

void treeTransform(Tree *tree, double (*dict)(const char *));

#endif  // EXPR_TREE_H
