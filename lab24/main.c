#include <stdio.h>

#include "expr_tree.h"

void printNode(const NodeUnion * node_union, NodeType node_type, void * context) {
    if (node_type == VALUE) {
        fprintf((FILE *) context, "%f ", node_union->value);
    }
    if (node_type == VARIABLE) {
        fprintf((FILE *) context, "%s ", node_union->variable);
    }
    if (node_type == OPERATOR) {
        fprintf((FILE *) context, "%c ", node_union->op.op);
    }
}

int main(void) {
    fromInfix("1 + 3 * (8 + 1)^11", printNode, stdout);

}
