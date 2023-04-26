#include "tree.h"
#include "stack.h"
#include <stdio.h>
#include <errno.h>

static void indent_print(tree_node * const node){
    printf("%f\n", node->value);
}

int main(void) {
    tree tr;
    tree_create(&tr);
    printf("%d\n", tree_insert(&tr, 0.01));
    printf("%d\n", tree_insert(&tr, 0.02));
    printf("%d\n", tree_insert(&tr, 3));
    printf("%d\n", tree_insert(&tr, 4));
    printf("%d\n",tree_contains(&tr, 0.03));
    tree_inorder_traversal(&tr, indent_print);
    return 0;
}
