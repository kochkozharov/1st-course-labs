#include "expr_tree.h"

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

typedef struct {
    Node *nodes[NODES_LENGTH];
    size_t size;
} Context;

typedef struct {
    double nums[NODES_LENGTH];
    size_t size;
} CalcContext;

typedef enum { ASSOC_LEFT, ASSOC_RIGHT } Assoc;

static double eval_pow(double a1, double a2) { return pow(a1, a2); }
static double eval_add(double a1, double a2) { return a1 + a2; }
static double eval_sub(double a1, double a2) { return a1 - a2; }
static double eval_mul(double a1, double a2) { return a1 * a2; }
static double eval_div(double a1, double a2) {
    if (!a2) {
        fprintf(stderr, "ERROR: Division by zero\n");
        exit(EXIT_FAILURE);
    }
    return a1 / a2;
}
static double eval_mod(double a1, double a2) {
    if (!a2) {
        fprintf(stderr, "ERROR: Division by zero\n");
        exit(EXIT_FAILURE);
    }
    return fmodf(a1, a2);
}

typedef struct {
    char op;
    int prec;
    Assoc assoc;
    bool unary;
    double (*eval)(double a1, double a2);
} OpType;

static OpType getOpType(char c) {
    switch (c) {
        case '^':
            return (OpType){.op = '^',
                            .prec = 2,
                            .assoc = ASSOC_RIGHT,
                            .unary = false,
                            .eval = eval_pow};
        case '*':
            return (OpType){.op = '*',
                            .prec = 1,
                            .assoc = ASSOC_LEFT,
                            .unary = false,
                            .eval = eval_mul};
        case '/':
            return (OpType){.op = '/',
                            .prec = 1,
                            .assoc = ASSOC_LEFT,
                            .unary = false,
                            .eval = eval_div};
        case '%':
            return (OpType){.op = '%',
                            .prec = 1,
                            .assoc = ASSOC_LEFT,
                            .unary = false,
                            .eval = eval_mod};
        case '+':
            return (OpType){.op = '+',
                            .prec = 0,
                            .assoc = ASSOC_LEFT,
                            .unary = false,
                            .eval = eval_add};
        case '-':
            return (OpType){.op = '-',
                            .prec = 0,
                            .assoc = ASSOC_LEFT,
                            .unary = false,
                            .eval = eval_sub};
    }
    return (OpType){.op = '\0',
                    .prec = -1,
                    .assoc = ASSOC_LEFT,
                    .unary = false,
                    .eval = NULL};
}

static bool isOp(char c) {
    return c == '^' || c == '*' || c == '/' || c == '%' || c == '+' || c == '-';
}

static void fromInfix(const char *expr,
                      void (*consume)(const NodeUnion *, NodeType,
                                      void *),  // (const *consume)
                      void *context) {
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
        } else if (expr[i] == ')') {
            while (!stackIsEmpty(&stack) && stackTop(&stack) != '(') {
                NodeUnion node_union = {.op = {.left = NULL,
                                               .right = NULL,
                                               .opChar = stackTop(&stack)}};
                NodeType node_type = OPERATOR;
                consume(&node_union, node_type, context);
                stackPopBack(&stack);
            }
            if (stackIsEmpty(&stack)) {
                fprintf(stderr, "ERROR: Incorrect parenthesis\n");
                exit(EXIT_FAILURE);
            }
            stackPopBack(&stack);
        } else if (isOp(expr[i])) {
            while (
                !stackIsEmpty(&stack) &&
                (getOpType(stackTop(&stack)).prec > getOpType(expr[i]).prec ||
                 (getOpType(stackTop(&stack)).prec == getOpType(expr[i]).prec &&
                  getOpType(expr[i]).assoc == ASSOC_LEFT))) {
                NodeUnion node_union = {.op = {.left = NULL,
                                               .right = NULL,
                                               .opChar = stackTop(&stack)}};
                NodeType node_type = OPERATOR;
                consume(&node_union, node_type, context);
                stackPopBack(&stack);
            }
            stackPushBack(&stack, expr[i]);
        } else if (isalpha(expr[i])) {
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
        } else if (isdigit(expr[i])) {
            char *end;
            double num = strtod(expr + i, &end);
            i = end - expr;
            NodeUnion node_union = {.value = num};
            NodeType node_type = VALUE;
            consume(&node_union, node_type, context);
            --i;
        } else {
            fprintf(stderr, "ERROR: incorrect character %c\n", expr[i]);
            exit(EXIT_FAILURE);
        }
        ++i;
    }
    while (!stackIsEmpty(&stack)) {
        if (stackTop(&stack) != '(') {
            NodeUnion node_union = {.op = {.left = NULL,
                                           .right = NULL,
                                           .opChar = stackTop(&stack)}};
            NodeType node_type = OPERATOR;
            consume(&node_union, node_type, context);
        }
        stackPopBack(&stack);
    }
    stackDestroy(&stack);
}

static void consumeToStream(const NodeUnion *node_union, NodeType node_type,
                            void *context) {
    if (node_type == VALUE) {
        fprintf((FILE *)context, "%f ", node_union->value);
    }
    if (node_type == VARIABLE) {
        fprintf((FILE *)context, "%s ", node_union->variable);
    }
    if (node_type == OPERATOR) {
        fprintf((FILE *)context, "%c ", node_union->op.opChar);
    }
}

void printPostfixFromInfix(FILE *file, const char *expr) {
    fromInfix(expr, consumeToStream, file);
    fprintf(file, "\n");
}

static void consumeToTree(const NodeUnion *node_union, NodeType node_type,
                          void *const ptr) {
    Context *const context = (Context *)ptr;
    Node *node = malloc(sizeof(Node));
    if (!node) abort();
    node->nodeUnion = *node_union;
    node->nodeType = node_type;
    if (node->nodeType == OPERATOR) {
        OpType op_type = getOpType(node->nodeUnion.op.opChar);
        if (!op_type.unary) {
            node->nodeUnion.op.right = context->nodes[--context->size];
            //node->nodeUnion.op.right->parent = node;
        }
        node->nodeUnion.op.left = context->nodes[--context->size];
        //node->nodeUnion.op.left->parent = node;
    }
    context->nodes[context->size++] = node;
}

void treeCreateFromInfix(Tree *const tree, const char *expr) {
    Context context = {.size = 0};

    fromInfix(expr, consumeToTree, &context);

    tree->root = context.size != 0 ? context.nodes[0] : NULL;
}

static void postorderDestroy(Node *const node) {
    if (node->nodeType == OPERATOR) {
        postorderDestroy(node->nodeUnion.op.left);
        postorderDestroy(node->nodeUnion.op.right);
    }
    free(node);
}

void treeDestroy(Tree *const tree) {
    Node *node = tree->root;
    if (node != NULL) {
        postorderDestroy(node);
    }
}

static void inorderPrint(FILE *file, const Node *const node, size_t _depth) {
    if (node->nodeType == OPERATOR) {
        inorderPrint(file, node->nodeUnion.op.right, _depth + 1);
        for (size_t i = 0; i < _depth; ++i) {
            fprintf(file, " ");
        }
        fprintf(file, "%c\n", node->nodeUnion.op.opChar);
        inorderPrint(file, node->nodeUnion.op.left, _depth + 1);
    } else {
        for (size_t i = 0; i < _depth; ++i) {
            fprintf(file, " ");
        }
        if (node->nodeType == VALUE)
            fprintf(file, "%f\n", node->nodeUnion.value);
        else
            fprintf(file, "%s\n", node->nodeUnion.variable);
    }
}

void treeInorderPrint(FILE *file, const Tree *const tree) {
    Node *node = tree->root;
    if (node != NULL) {
        inorderPrint(file, node, 0);
    }
}

static void postorderCalculate(const Node *const node, void *const ptr,
                               double (*dict)(const char *)) {
    CalcContext *const context = (CalcContext *)ptr;
    if (node->nodeType == OPERATOR) {
        postorderCalculate(node->nodeUnion.op.left, context, dict);
        postorderCalculate(node->nodeUnion.op.right, context, dict);
        OpType op_type = getOpType(node->nodeUnion.op.opChar);
        double y = context->nums[--context->size];
        double x = context->nums[--context->size];
        context->nums[context->size++] = op_type.eval(x, y);
    } else if (node->nodeType == VALUE) {
        context->nums[context->size++] = node->nodeUnion.value;
    } else {
        context->nums[context->size++] = dict(node->nodeUnion.variable);
    }
}

double treeCalculate(const Tree *const tree, double (*dict)(const char *)) {
    CalcContext calc_context = {.size = 0};
    Node *node = tree->root;
    assert(node != NULL);
    postorderCalculate(node, &calc_context, dict);
    assert(calc_context.size == 1);
    return calc_context.nums[0];
}
/*
static Node *nodeDeepCopy(Node *const node) {
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) abort();
    memcpy(new_node, node, sizeof(Node));
    if (node && node->nodeType != OPERATOR) {
        return new_node;
    }
    new_node->nodeUnion.op.left = nodeDeepCopy(node->nodeUnion.op.left);
    new_node->nodeUnion.op.right = nodeDeepCopy(node->nodeUnion.op.right);
    return new_node;
}
*/

static void postorderTransform(Node *const node, double (*dict)(const char *)) {
    if (node->nodeType == OPERATOR) {
        postorderTransform(node->nodeUnion.op.left, dict);
        postorderTransform(node->nodeUnion.op.right, dict);
    }
    Operator cur = node->nodeUnion.op;
    if ((cur.opChar == '+') && ((cur.left->nodeType == VALUE &&
            cur.left->nodeUnion.value == 0) ||
        (cur.left->nodeType == VARIABLE &&
            dict(cur.left->nodeUnion.variable) == 0)) ) {
        *node = *cur.right;
        free(cur.right);
        free(cur.left);
    }
    else if ((cur.opChar == '+' || cur.opChar == '-') && ((cur.right->nodeType == VALUE &&
            cur.right->nodeUnion.value == 0) ||
        (cur.right->nodeType == VARIABLE &&
            dict(cur.right->nodeUnion.variable) == 0)) ) {
        *node = *cur.left;
        free(cur.left);
        free(cur.right);
    }
}

void treeTransform(Tree *const tree, double (*dict)(const char *)) {
    Node *node = tree->root;
    postorderTransform(node, dict);
}
