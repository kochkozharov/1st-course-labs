#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "expr_tree.h"
#include "stack.h"

typedef struct {
    Node *nodes[NODES_LENGTH];
    size_t size;
} Context;

enum {ASSOC_LEFT, ASSOC_RIGHT};

static double eval_pow(double a1, double a2) { return pow(a1, a2); }
static double eval_add(double a1, double a2) { return a1+a2; }
static double eval_sub(double a1, double a2) { return a1-a2; }
static double eval_mul(double a1, double a2) { return a1*a2; }
static double eval_div(double a1, double a2) {
  if(!a2) {
    fprintf(stderr, "ERROR: Division by zero\n");
    exit(EXIT_FAILURE);
  }
  return a1/a2;
}
static double eval_mod(double a1, double a2) {
  if(!a2) {
    fprintf(stderr, "ERROR: Division by zero\n");
    exit(EXIT_FAILURE);
  }
  return fmodf(a1, a2);
}

typedef struct {
  char op;
  int prec;
  int assoc;
  bool unary;
  double (*eval)(double a1, double a2);
} OpType;

static OpType getOpType(char c) {
    switch(c)
    {
        case '^':
        return (OpType) {.op = '^', .prec = 2, .assoc = ASSOC_RIGHT, 
                         .unary = false, .eval = eval_pow};
        case '*':
        return (OpType) {.op = '*', .prec = 1, .assoc = ASSOC_LEFT, 
                         .unary = false, .eval = eval_mul};
        case '/':
        return (OpType) {.op = '/', .prec = 1, .assoc = ASSOC_LEFT, 
                         .unary = false, .eval = eval_div};
        case '%':
        return (OpType) {.op = '%', .prec = 1, .assoc = ASSOC_LEFT, 
                         .unary = false, .eval = eval_mod};
        case '+':
        return (OpType) {.op = '+', .prec = 0, .assoc = ASSOC_LEFT, 
                         .unary = false, .eval = eval_add};
        case '-':
        return (OpType) {.op = '-', .prec = 0, .assoc = ASSOC_LEFT, 
                         .unary = false, .eval = eval_sub};
    }
    return (OpType) {.op = '\0', .prec = -1, .assoc = ASSOC_LEFT, .unary = false, .eval = NULL};
}

static bool isOp(char c) {
    return c == '^' || c == '*' || c == '/' || c == '%' || c == '+' || c == '-';
}

static void fromInfix(
    const char *expr,
    void (*consume)(const NodeUnion *, NodeType, void *), // (const *consume)
    void *context
) {
    size_t n = strlen(expr);
    size_t i = 0;
    Stack stack;
    stackCreate(&stack);
    while (i < n) {
        if (expr[i] == ' ') {
            ++i;
            continue;
        }
        if (expr[i] == '(') {
            stackPushBack(&stack, '(');
        }
        else if (expr[i] == ')') {
            while (!stackIsEmpty(&stack) &&  stackTop(&stack) !=  '(') {
                NodeUnion node_union = { .op = { .left = NULL, .right = NULL, .opChar = stackTop(&stack)} };
                NodeType node_type = OPERATOR;
                consume(&node_union, node_type, context);
                stackPopBack(&stack);
            }
            if (stackIsEmpty(&stack)) {
                fprintf(stderr, "ERROR: Incorrect parenthesis\n");
                exit(EXIT_FAILURE);
            }
            stackPopBack(&stack);
        }
        else if (isOp(expr[i])) {
            while (!stackIsEmpty(&stack) && (getOpType(stackTop(&stack)).prec > getOpType(expr[i]).prec || 
                  (getOpType(stackTop(&stack)).prec == getOpType(expr[i]).prec &&
                  getOpType(expr[i]).assoc == ASSOC_LEFT))) {
                NodeUnion node_union = { .op = { .left = NULL, .right = NULL, .opChar = stackTop(&stack)} };
                NodeType node_type = OPERATOR;
                consume(&node_union, node_type, context);
                stackPopBack(&stack);
            }
            stackPushBack(&stack, expr[i]);
        }
        else if (isalpha(expr[i])) {
            size_t start = i;
            do {
                ++i;
            } while (isalpha(expr[i]));
            if (i - start > VARIABLE_LENGTH - 1) {
                fprintf(stderr, "ERROR: Too long name of variable\n");
                exit(EXIT_FAILURE);
            }
            NodeUnion node_union;
            memcpy(node_union.variable, expr + start, i - start);
            node_union.variable[i - start] = '\0';
            NodeType node_type = VARIABLE;
            consume(&node_union, node_type, context);
            --i;
        }
        else if (isdigit(expr[i])) {
            char *end;
            double num = strtod(expr + i, &end);
            i = end - expr;
            NodeUnion node_union = {.value = num};
            NodeType node_type = VALUE;
            consume(&node_union, node_type, context);
            --i;
        }
        else {
            fprintf(stderr, "ERROR: incorrect character %c\n", expr[i]);
            exit(EXIT_FAILURE);
        }
        ++i;
    }
    while (!stackIsEmpty(&stack)) {
        if (stackTop(&stack) != '(') {
            NodeUnion node_union = { .op = { .left = NULL, .right = NULL, .opChar = stackTop(&stack)} };
            NodeType node_type = OPERATOR;
            consume(&node_union, node_type, context);
        }
        stackPopBack(&stack);
    }

    stackDestroy(&stack);

}

static void consumeToStream(const NodeUnion * node_union, NodeType node_type, void * context) {
    if (node_type == VALUE) {
        fprintf((FILE *) context, "%f ", node_union->value);
    }
    if (node_type == VARIABLE) {
        fprintf((FILE *) context, "%s ", node_union->variable);
    }
    if (node_type == OPERATOR) {
        fprintf((FILE *) context, "%c ", node_union->op.opChar);
    }
}

void printPostfixFromInfix(FILE *file, const char *expr) {
    fromInfix(expr, consumeToStream, file);
    fprintf(file, "\n");
}

static void consumeToTree(
    const NodeUnion *node_union,
    NodeType node_type,
    void * const ptr
) {
    Context * const context = (Context *) ptr;
    Node *node = malloc(sizeof(Node));
    node->nodeUnion = *node_union;
    node->nodeType = node_type;
    if (node->nodeType == OPERATOR) {
        OpType op_type = getOpType(node->nodeUnion.op.opChar);
        node->nodeUnion.op.left = context->nodes[--context->size];
        node->nodeUnion.op.left->parent = node;
        if (!op_type.unary) {
            node->nodeUnion.op.right = context->nodes[--context->size];
            node->nodeUnion.op.right->parent = node;
        }
    }
    context->nodes[context->size++] = node;
}

void treeCreateFromInfix(Tree * const tree, const char *expr) {
    
    Context context = {.size = 0};

    fromInfix(expr, consumeToTree, &context);

    tree->root = context.size != 0 ? context.nodes[0] : NULL;
}

static void postorderDestroy(Node *node) {
    if (node->nodeType == OPERATOR) {
        postorderDestroy(node->nodeUnion.op.left);
        postorderDestroy(node->nodeUnion.op.right);
    }
    free(node);
}

void treeDestroy(Tree * const tree) {
    Node *node = tree->root;
    if (node != NULL) {
        postorderDestroy(node);
    }
}

static void inorderPrint(FILE *file, Node * const node,  size_t _depth) {
    
    if (node->nodeType == OPERATOR) {
        inorderPrint(file, node->nodeUnion.op.left,  _depth+1);
        for (size_t i=0; i < _depth; ++i) {
            fprintf(file, " ");
        }
        fprintf(file, "%c\n", node->nodeUnion.op.opChar);
        inorderPrint(file, node->nodeUnion.op.right,  _depth+1);
    }
    else {
        for (size_t i=0; i < _depth; ++i) {
            fprintf(file, " ");
        }
        if (node->nodeType == VALUE) fprintf(file, "%f\n", node->nodeUnion.value);
        else fprintf(file, "%s\n", node->nodeUnion.variable);
    }
}

void treeInorderPrint(FILE *file, Tree * const tree) {
    Node *node = tree->root;
    if (node != NULL) {
        inorderPrint(file, node, 0);
    }
}

void tree_transform(Tree * const tree) {
    (void) tree;
}