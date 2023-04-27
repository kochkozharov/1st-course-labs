#include "tree_func.h"
#include "tree.h"


static size_t max_depth(const tree_node * const  node)
{
    if (node == NULL || (!node->left && !node->right))
        return 0;
    else {
        size_t l_depth = max_depth(node->left);
        size_t r_depth = max_depth(node->right);
        if (l_depth > r_depth)
            return l_depth + 1;
        else
            return r_depth + 1;
    }
}

size_t tree_depth(const tree * const tree) {
    return max_depth(tree->root);
}
