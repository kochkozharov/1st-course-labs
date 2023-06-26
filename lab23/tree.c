#include "tree.h"
#include "stack.h"
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void tree_clear(tree * const tree) {
    tree->size=0;
    tree_node * node = tree->root;
    tree_node * last_visited_node = NULL;
    stack st;
    stack_create(&st);
    while(!stack_is_empty(&st) || node) {
        if (node) {
            stack_push_back(&st, node);
            node = node->right;
        }
        else {
            tree_node * top_node;
            stack_top(&st, &top_node);
            if (top_node->left && (last_visited_node != top_node->left))
                node=top_node->left;
            else {
                free(top_node);
                stack_top(&st, &last_visited_node);
                stack_pop_back(&st);
            }
        }
    }
    stack_destroy(&st);
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
//static because UB when value is not in tree
static size_t tree_node_depth(const tree * const tree, const tree_t value) {
    tree_node *node = tree->root;
    size_t depth = 0;
    while (node != NULL || (!tree->root->right && !tree->root->left)) {
        if (node->value > value) {
            depth++;
            node = node->left;
        }
        else if (node->value < value) {
            depth++;
            node = node->right;
        }
        else
            return depth;
    }
    return 0;
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
        else {
            break;
        }
    }

    if (*ptr == NULL) {
        errno = EINVAL;
        return -1;
    }
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
    } else if (node->right != NULL) {
        assert(node->left == NULL);
        *ptr = node->right;
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
        if (value < node->value)
            ptr = &node->left;
        else if (value > node->value) 
            ptr = &node->right;
        else {
            errno = EINVAL;
            return -1;
        }
    }
    *ptr = malloc(sizeof(tree_node));
    if (*ptr == NULL)
        return -1;
    ++tree->size;
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

void tree_print_postorder(const tree * const tree) {
    if (tree_is_empty(tree)) {
        printf("EMPTY\n");
        return;
    }
    tree_node * node = tree->root;
    tree_node * last_visited_node = NULL;
    stack st;
    stack_create(&st);
    while(!stack_is_empty(&st) || node) {
        if (node) {
            stack_push_back(&st, node);
            node = node->right;
        }
        else {
            tree_node * top_node;
            stack_top(&st, &top_node);
            if (top_node->left && (last_visited_node != top_node->left))
                node=top_node->left;
            else {
                for(size_t i=0;i<tree_node_depth(tree,top_node->value);i++) printf(" ");
                printf(TREE_FORMAT_STR, top_node->value);
                stack_top(&st, &last_visited_node);
                stack_pop_back(&st);
            }
        }
    }
    stack_destroy(&st);
}

void tree_print_preorder(const tree * const tree) {
    if (tree_is_empty(tree)) {
        printf("EMPTY\n");
        return;
    }
    tree_node * node = tree->root;
    stack st;
    stack_create(&st);
    stack_push_back(&st,node);
    while (!stack_is_empty(&st)) {
        stack_top(&st, &node);
        stack_pop_back(&st);
        for(size_t i=0;i<tree_node_depth(tree,node->value);i++) printf(" ");
        printf(TREE_FORMAT_STR, node->value);
        if (node->right)
            stack_push_back(&st, node->right);
        if (node->left)
            stack_push_back(&st, node->left);
    } 
    stack_destroy(&st);
}

void tree_print_inorder(const tree * const tree) {
    if (tree_is_empty(tree)) {
        printf("EMPTY\n");
        return;
    }
    tree_node * node = tree->root;
    stack st;
    stack_create(&st);
    while (!stack_is_empty(&st) || node) {
        if (node) {
            stack_push_back(&st, node);
            node = node->right;
        }
        else {
            stack_top(&st, &node);
            stack_pop_back(&st);
            for(size_t i=0;i<tree_node_depth(tree,node->value);i++) printf(" ");
            printf(TREE_FORMAT_STR, node->value);
            node = node->left;
        }
    }
    stack_destroy(&st);
}


/*
Обязательно: Pre-order In-order Post-order
На 5: обход не рекурсивно
На карму: +1 реализовать обход в ширину без доп памяти n^2
Опционально (не обязательно): +1 карма реализовать дерево общего вида.
*/
