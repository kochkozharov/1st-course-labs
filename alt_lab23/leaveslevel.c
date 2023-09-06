#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tree.h"
#include "leaveslevel.h"

static int max_level(node *t, int deep){ //Находит максимальный уровень
    if(t == NULL)
        return deep - 1;
    return max(max_level(t->son, deep + 1), max_level(t->brother, deep));
}

static bool rec_task(node *t, int curDeep, int deep, bool *stop){ //Идея: Если уровень листа не совпадает с максимальным уровнем, то не выполняется условие
    if (t == NULL || *stop){
        return true;
    }
    if (t->son == NULL && curDeep != deep){
        *stop = true;
        return false;
    }
    return rec_task(t->brother, curDeep, deep, stop) && rec_task(t->son, curDeep + 1, deep, stop); 
}

bool task(node *t) {
    bool stop = false;
    return rec_task(t, 0, max_level(t, 0), &stop);
}