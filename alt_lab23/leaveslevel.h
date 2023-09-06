#ifndef _LEAVESLEVEL_H_
#define _LEAVESLEVEL_H_

#include "tree.h"
#define max(x,y) ((x) > (y) ? (x) : (y))

int max_level(node *t, int deep);

bool task(node *t, int curDeep, int deep);

#endif