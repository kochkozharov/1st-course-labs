#include "tree.h"
#include "stack.h"
#include <stdio.h>
#include <errno.h>


int main(void) {
    tree tr;
    tree_create(&tr);
    printf("%d\n", tree_insert(&tr, 0.01));
    printf("%d\n", tree_insert(&tr, 0.01));
    perror("");
    stack st;
    stack_create(&st);
    t topvalue;
    if (stack_top(&st, &topvalue)!=0) perror("stack_top");
}
