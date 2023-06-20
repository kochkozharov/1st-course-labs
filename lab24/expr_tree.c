#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "expr_tree.h"
#include "stack.h"

double eval_pow(double a1, double a2) { return pow(a1, a2); }
double eval_add(double a1, double a2) { return a1+a2; }
double eval_sub(double a1, double a2) { return a1-a2; }
double eval_exp(double a1, double a2) { return a2<0 ? 0 : (a2==0?1:a1*eval_exp(a1, a2-1)); }
double eval_mul(double a1, double a2) { return a1*a2; }
double eval_div(double a1, double a2) {
  if(!a2) {
    fprintf(stderr, "ERROR: Division by zero\n");
    exit(EXIT_FAILURE);
  }
  return a1/a2;
}
double eval_mod(double a1, double a2) {
  if(!a2) {
    fprintf(stderr, "ERROR: Division by zero\n");
    exit(EXIT_FAILURE);
  }
  return fmodf(a1, a2);
}

enum {ASSOC_LEFT, ASSOC_RIGHT};

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

void fromInfix(
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
                NodeUnion node_union = { .op = { .left = NULL, .right = NULL, .op = stackTop(&stack)} };
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
                NodeUnion node_union = { .op = { .left = NULL, .right = NULL, .op = stackTop(&stack)} };
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
        NodeUnion node_union = { .op = { .left = NULL, .right = NULL, .op = stackTop(&stack)} };
        NodeType node_type = OPERATOR;
        consume(&node_union, node_type, context);
        stackPopBack(&stack);
    }
    stackDestroy(&stack);
}