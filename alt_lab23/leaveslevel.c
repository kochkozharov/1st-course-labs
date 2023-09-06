#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"
#include "leaveslevel.h"

int max_level(node *t, int deep){ //Находит максимальный уровень
    if(t == NULL)
        return deep - 1;
    return max(max_level(t->son, deep + 1), max_level(t->brother, deep));
}

bool task(node *t, int curDeep, int deep){ //Идея: Если уровень листа не совпадает с максимальным уровнем, то не выполняется условие
    if (t == NULL){
        return false;
    }
    if (t->son == NULL && curDeep != deep){
        return true;
    }
    return task(t->brother, curDeep, deep) || task(t->son, curDeep + 1, deep); 
}