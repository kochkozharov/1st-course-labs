#ifndef EXPR_TREE_H
#define EXPR_TREE_H

#include <stddef.h>

#define VARIABLE_LENGTH (16U)
#define NODES_LENGTH (512U)

typedef struct Node Node;

typedef struct {
    Node *left, *right;
    char op;
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

typedef struct {
    Node nodes[NODES_LENGTH];
    size_t size;
} Context;

void fromInfix(
    const char *expr,
    void (*consume)(const NodeUnion *, NodeType, void *),
    void *context
);

#endif //EXPR_TREE_H
