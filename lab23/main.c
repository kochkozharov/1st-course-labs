#include "tree.h"
#include "stack.h"
#include <stdio.h>
#include <errno.h>

int main(void) {
    tree tr;
    tree_create(&tr);
    printf("%d\n", tree_insert(&tr, 2));
    printf("%d\n", tree_insert(&tr, 1));
    printf("%d\n", tree_insert(&tr, 4));
    printf("%d\n", tree_insert(&tr, 3));
    printf("%d\n", tree_insert(&tr, 6));
    printf("%d\n", tree_insert(&tr, 9));
    printf("%d\n", tree_insert(&tr, 0));
    printf("%d\n", tree_insert(&tr, 1.5));
    printf("%d\n", tree_insert(&tr, 2.9));
    printf("------------\n");
    tree_print_preorder(&tr);
    printf("------------\n");
    tree_print_inorder(&tr);
    printf("------------\n");
    tree_print_postorder(&tr);
    return 0;
}
