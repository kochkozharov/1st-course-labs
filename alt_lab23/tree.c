#include "tree.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

node *create_node(float f, node *par) {
    node *t;
    t = (node *)malloc(sizeof(node));
    t->value = f;
    t->son = NULL;
    t->brother = NULL;
    t->parent = par;
    return t;
}

Tree *create_tree(float f) {
    Tree *t;
    t = (Tree *)malloc(sizeof(Tree));
    t->root = create_node(f, NULL);
    return t;
}

node *search_tree(node *t, float f) {
    if (t == NULL)
        return t;
    node *tree = NULL;
    if (t->value == f)
        return t;
    if (t->son != NULL)
        tree = search_tree(t->son, f);
    if (tree == NULL)
        tree = search_tree(t->brother, f);
    return tree;
}

void add_node_in_tree(Tree *tree, float par_f, float f) {
    node *t = tree->root;
    t = search_tree(t, par_f);
    if (t == NULL)
        return;
    if (t->son == NULL) {
        t->son = create_node(f, t);
    } else {
        t = t->son;
        while (t->brother != NULL) {
            t = t->brother;
        }
        t->brother = create_node(f, t->parent);
    }
}

void delete_node(Tree *tree, float f) {
    node *t = tree->root;
    t = search_tree(t, f);
    if (t == NULL)
        return;
    if (t->parent == NULL) {
        if (t->son != NULL)
            delete (t->son);
        free(t);
        return;
    }
    if (t->parent->son == t) {
        t->parent->son = t->brother;
    } else {
        node *tr = t->parent->son;
        while (tr->brother != t) {
            tr = tr->brother;
        }
        tr->brother = t->brother;
    }
    if (t->son != NULL)
        delete (t->son);
    free(t);
}

void delete(node *t) {
    if (t->son != NULL)
        delete (t->son);
    if (t->brother != NULL)
        delete (t->brother);
    free(t);
}

void preOrder(node *t, int curDeep) {
    if (t == NULL)
        return;
    for (int i = 0; i < curDeep; i++)
        printf("\t");
    printf("%-.2f\n", t->value);
    preOrder(t->son, curDeep + 1);
    preOrder(t->brother, curDeep);
}

void postOrder(node *t) {
    if (t == NULL)
        return;
    postOrder(t->son);
    printf("%-.2f\n", t->value);
    postOrder(t->brother);
}
