#include "tree.h"
#include "tree_func.h"
#include "stack.h"

size_t tree_depth(const tree * const tree)
{
    if (tree_is_empty(tree)) return 0;
    size_t max_depth = 0;
    tree_node * node = tree->root;
    stack st;
    stack_create(&st);
    stack_push_back(&st,node);
    while (!stack_is_empty(&st)) {
        stack_top(&st, &node);
        stack_pop_back(&st);
        max_depth = node->depth > max_depth ? node->depth : max_depth;
        if (node->right)
            stack_push_back(&st, node->right);
        if (node->left)
            stack_push_back(&st, node->left);
    } 
    stack_destroy(&st);
    return max_depth;
}
