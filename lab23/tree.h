#ifndef _TREE_H_
#define _TREE_H_

#include <stdbool.h>
#include <stddef.h>
#include "types.h"

typedef struct treeNode treeNode;

typedef struct {
    treeNode *root;
    size_t size;
} tree;

void tree_clear(tree *tree);

bool tree_contains(const tree *tree, t value);

void tree_create(tree *tree);

int tree_erase(tree * const tree, t value);

int tree_insert(tree * const tree, t value);

int tree_get(const tree *tree, size_t index, t *value);

int tree_set(tree *tree, size_t index, t value);

size_t tree_size(const tree *tree);

void tree_destroy(tree *tree);

#endif // _TREE_H_
