#ifndef _TREE_H_
#define _TREE_H_
#include <stdbool.h>
#include <stddef.h>

typedef float tree_t;

typedef struct tree_node {
    struct tree_node * parent, * left, * right;
    tree_t value;
} tree_node;

typedef struct {
    tree_node * root;
    size_t size;
} tree;

void tree_clear(tree * tree);

bool tree_contains(const tree * tree, tree_t value);

void tree_create(tree * tree);

int tree_erase(tree * tree, tree_t value);

int tree_insert(tree * tree, tree_t value);

size_t tree_size(const tree * tree);

void tree_destroy(tree * tree);

void tree_print_preorder(tree * tree);

void tree_print_inorder(tree * tree);

void tree_print_postorder(tree * tree);

#endif // _TREE_H_
