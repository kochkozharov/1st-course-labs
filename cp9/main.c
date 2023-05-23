#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "vector.h"
#include "utils.h"
#include "string.h"

static char *inputString(FILE* fp){
    size_t size = 16;
    char *str;
    int ch;
    size_t len = 0;
    str = malloc(size);
    if (!str) return str;
    while((ch=fgetc(fp)) != '\n'){
        if (ch == EOF) {
            if (len==0) {
                free(str);
                return NULL;
            }
            else break;
        };
        str[len++]=ch;
        if(len==size) {
            str = realloc(str, size*=2);
            if (!str) return str;
        }
    }
    str[len++]='\0';
    return realloc(str, len);
}

int main(void){
    Vector table;
    vectorCreate(&table);
    char *str;
    for (;;) {
        str = inputString(stdin);
        if (!str) break;
        char *val;
        size_t i = 0;
        bool comma_is_found=false;
        while (str[i]!='\0') {
            if (str[i]==';' && i < KEY_SIZE) {
                str[i]='\0';
                val = str+i+1;
                comma_is_found = true;
                break;
            }
            ++i;
        }
        if (!comma_is_found) exit(EXIT_FAILURE);
        size_t val_size = strlen(val)+1;
        printf("%ld\n",val_size);
        /*
        Data *line = malloc(sizeof(Data)+val_size);
        memset(line->key,0,KEY_SIZE);
        for (size_t j=0; j<i;++j) {
            line->key[j]=key[i];
        }
        memcpy(line->value,val,val_size);
        vectorPushBack(&table, line);
        */
        free(str);
    }
    return 0;
}
// _ _ _ _ _
