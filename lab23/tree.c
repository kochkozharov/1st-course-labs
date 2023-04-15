#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

#include "tree.h"
#include "types.h"

struct treeNode {
    treeNode *parent, *left, *right;
    t value;
};


void tree_clear(tree * const tree) {
    tree->size=0;
    /* non-recursive post-order */;
}

bool tree_contains(const tree * const tree, const t value) {
    treeNode *node = tree->root;
    while (node != NULL) {
        if (node->value > value)
            node = node->left;
        else if (node->value < value)
            node = node->right;
        else
            return true;
    }
    return false;
}

void tree_create(tree * const tree) {
    tree->root = NULL;
    tree->size = 0;
}

int tree_erase(tree * const tree, const t value) {
    treeNode **ptr = &tree->root, *node = NULL;
    while (*ptr != NULL) {
        node = *ptr;
        if (node->value > value)
            ptr = &node->left;
        else if (node->value < value)
            ptr = &node->right;
        else
            break;
    }
    if (node == NULL)
        return EINVAL;

    assert(node->value == value);
    if (node->left != NULL && node->right != NULL) {
        t * const value = &node->value;
        ptr = &node->right;
        node = node->right;
        while (node->left != NULL) {
            ptr = &node->left;
            node = node->left;
        }
        *value = node->value;
    }
    if (node->left != NULL) {
        assert(node->right == NULL);
        *ptr = node->left;
        node->left->parent = node->parent;
    } else if (node->right != NULL) {
        assert(node->left == NULL);
        *ptr = node->right;
        node->right->parent = node->parent;
    } else
        *ptr = NULL;
    free(node);
    --tree->size;
    return 0;
}

int tree_insert(tree * const tree, const t value) {
    treeNode **ptr = &tree->root, *node = NULL;
    while (*ptr != NULL) {
        node = *ptr;
        if (node->value > value)
            ptr = &node->left;
        else if (node->value < value)
            ptr = &node->right;
        else
            return EINVAL;
    }
    *ptr = malloc(sizeof(treeNode));
    if (*ptr == NULL)
        return errno;
    ++tree->size;
    (*ptr)->parent = node;
    (*ptr)->left = NULL;
    (*ptr)->right = NULL;
    (*ptr)->value = value;
    return 0;
}

bool tree_is_empty(const tree * const tree) {
    return tree->size == 0;
}

size_t tree_size(const tree * const tree) {
    return tree->size;
}

void tree_destroy(tree * const tree) {
    tree_clear(tree);
}


/*
Обязательно: Pre-order In-order Post-order
На 5: обход не рекурсивно
На карму: +1 реализовать обход в ширину без доп памяти n^2
Опционально (не обязательно): +1 карма реализовать дерево общего вида.
*/
