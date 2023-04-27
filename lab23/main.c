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
        "add n - добавить узел со значением n\n\
        delete n - удалить узел со знгаченим n\n\
        preorder - КЛП обход\n\
        inorder - ЛКП обход\n\
        postorder - ЛПК обход\n\
        clear - уничтожить дерево\n\
        depth - вывести глубину дерева\n\
        quit - выход\n"
    );
}

int main(void) {
    printf("Type \"help\" for help\n");
    tree tr;
    tree_create(&tr);
    bool flag = true;
    while(flag){
        char str[32];
        fgets(str,32,stdin);
        char delim[] = " ";
        char * command = strtok(str, delim);
        if (command) {
            char * key = strtok(NULL, delim);
            if (strcmp(command, "add")==0 && key) {
                if (tree_insert(&tr, atof(key))) perror("");
            }
            else if (strcmp(command, "delete")==0 && key) {
                if (tree_erase(&tr, atof(key))) perror("");
            }
            else if (strcmp(command, "preorder\n")==0)
                tree_print_preorder(&tr);
            else if (strcmp(command, "inorder\n")==0)
                tree_print_inorder(&tr);
            else if (strcmp(command, "postorder\n")==0)
                tree_print_postorder(&tr);
            else if (strcmp(command, "help\n")==0)
                help();
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
