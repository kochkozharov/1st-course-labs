#include "tree.h"
#include "stack.h"
#include <stdio.h>
#include <errno.h>

static void indent_print(tree_node * const node){
    for (size_t i=0; i< node->depth; i++) {
        printf(" ");
    }
    printf("%f\n", node->value);
}

int main(void) {
    tree tr;
    tree_create(&tr);
    printf("%d\n", tree_insert(&tr, 2));
    printf("%d\n", tree_insert(&tr, 1));
    printf("%d\n", tree_insert(&tr, 4));
    printf("%d\n", tree_insert(&tr, 3));
    printf("%d\n",tree_contains(&tr, 0.03));
    tree_inorder_traversal(&tr, indent_print);
    return 0;
}
