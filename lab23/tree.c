#include "tree.h"
#include "stack.h"
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void tree_clear(tree * const tree) {
    tree->size=0;
    /* non-recursive post-order */;
}

bool tree_contains(const tree * const tree, const tree_t value) {
    tree_node *node = tree->root;
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

int tree_erase(tree * const tree, const tree_t value) {
    tree_node **ptr = &tree->root, *node = NULL;
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
        errno = EINVAL;
        return -1;

    assert(node->value == value);
    if (node->left != NULL && node->right != NULL) {
        tree_t * const value = &node->value;
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

int tree_insert(tree * const tree, const tree_t value) {
    tree_node **ptr = &tree->root, *node = NULL;
    while (*ptr != NULL) {
        node = *ptr;
        if (node->value > value)
            ptr = &node->left;
        else if (node->value < value) 
            ptr = &node->right;
        else
            errno = EINVAL;
            return -1;
    }
    *ptr = malloc(sizeof(tree_node));
    if (*ptr == NULL)
        return -1;
    ++tree->size;
    if (!node) {
        (*ptr)->depth = 0;
    }
    else {
        (*ptr)->depth = node->depth+1;
    }
    (*ptr)->parent = node;
    (*ptr)->left = NULL;
    (*ptr)->right = NULL;
    (*ptr)->value = value;
    printf("%f\n",value);
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

void tree_inorder_traversal(tree * const tree, void (* process)(tree_node * node)) {
    tree_node * node = tree->root;
    stack st;
    stack_create(&st);
    bool done = false;
    while (!done) {
        if (node) {
            stack_push_back(&st, node);
            node = node->left;
        }
        else if (stack_is_empty(&st)) {
            done = true;
        }
        stack_top(&st, &node);
        stack_pop_back(&st);
        process(node);
        node = node->right;
    }
    stack_destroy(&st);
}


/*
Обязательно: Pre-order In-order Post-order
На 5: обход не рекурсивно
На карму: +1 реализовать обход в ширину без доп памяти n^2
Опционально (не обязательно): +1 карма реализовать дерево общего вида.
*/
