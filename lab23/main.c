#include "tree.h"
#include "stack.h"
#include "tree_func.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>

#define COMMAND_LEN 32

static void help() {
    printf(
        "add n - добавить узел со значением n\n"
        "delete n - удалить узел со знгаченим n\n"
        "preorder - КЛП обход\n"
        "inorder - ЛКП обход\n"
        "postorder - ЛПК обход\n"
        "clear - уничтожить дерево\n"
        "depth - вывести глубину дерева\n"
        "quit - выход\n"
    );
}

static void example(tree * tree) {
    tree_insert(tree, 8);
    tree_insert(tree, 9);
    tree_insert(tree, 1);
    tree_insert(tree, 2);
    tree_insert(tree, -2);
    tree_insert(tree, 2.3);
    tree_insert(tree, 10);
    tree_insert(tree, 11);
    tree_insert(tree, 10.5);
    tree_insert(tree, 5);
    tree_insert(tree, 0);
    tree_insert(tree, 9.5);
}

int main(void) {
    printf("Type \"help\" for help\n");
    tree tr;
    tree_create(&tr);
    bool flag = true;
    while(flag){
        char str[32];
        printf(">");
        fgets(str,32,stdin);
        
        char delim[] = " ";
        
        char * command = strtok(str, delim);
        
        if (command) {
            char *key = strtok(NULL, delim);
            char *err_ptr;
            float f_key;
            if (key) {
                f_key = strtof(key, &err_ptr);
            }
            else {
                err_ptr=NULL;
            }
            if (strcmp(command, "add")==0 && key && err_ptr && *err_ptr == '\n') {
                if (tree_insert(&tr, f_key)) perror("");
            }
            else if (strcmp(command, "delete")==0 && key && err_ptr &&*err_ptr == '\n') {
                if (tree_erase(&tr, f_key)) perror("");
            }
            else if (strcmp(command, "preorder\n")==0)
                tree_print_preorder(&tr);
            else if (strcmp(command, "inorder\n")==0)
                tree_print_inorder(&tr);
            else if (strcmp(command, "postorder\n")==0)
                tree_print_postorder(&tr);
            else if (strcmp(command, "help\n")==0)
                help();
            else if (strcmp(command, "ex\n")==0)
                example(&tr);
            else if (strcmp(command, "clear\n")==0) {
                tree_clear(&tr);
                tree_create(&tr);
            }
            else if (strcmp(command, "depth\n")==0)
                printf("%ld\n", tree_depth(&tr));
            else if (strcmp(command, "quit\n")==0)
                flag=false;
            else printf("Invalid input\n");
        }
    }
    return 0;
}
