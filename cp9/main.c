#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "vector.h"
#include "utils.h"
#include "string.h"
#include "data.h"

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
    FILE *table_txt=fopen("table.txt","r");
    if (!table_txt) exit(EXIT_FAILURE);
    Vector vtable;
    vectorCreate(&vtable);
    char *str;
    for (;;) {
        str = inputString(table_txt);
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
        char *key = str;
        size_t val_size = strlen(val)+1;
        size_t real_key_size = strlen(key)+1;
        Data *line = malloc(sizeof(Data)+val_size);
        memcpy(line->key,key,real_key_size);
        memcpy(line->value,val,val_size);
        vectorPushBack(&vtable, line);
        free(str);
    }
    fclose(table_txt);

    Data ** table = vectorData(&vtable);
    size_t lines_count = vectorSize(&vtable);
    /*
    bool is_sorted = true;
    for (size_t i =1; i < vectorSize(&vtable);++i) {
        if (cmpData(table[i],table[i-1]) < 0) {
            is_sorted = false;
            break;
        }
    }

    bool is_reverse_sorted = true;
    for (size_t i =1; i < vectorSize(&vtable);++i) {
        if (cmpData(table[i],table[i-1]) > 0) {
            is_reverse_sorted = false;
            break;
        }
    }
    */
    for (size_t i=0;i < lines_count;++i){
        printf("%s %s\n",table[i]->key,table[i]->value);
    }
    qsort(table,lines_count,sizeof(Data*),cmpData);
    printf("---------\n");
    for (size_t i=0;i < lines_count;++i){
        printf("%s %s\n",table[i]->key,table[i]->value);
    }
    printf("---------\n");
    for (;;) {
        str = inputString(stdin);
        if (!str) break;
        Data **res = binarySearch(&str,table,lines_count,sizeof(Data*),cmpStrWithData);
        if (!res) printf("N/A\n");
        else {
            Data **end = table + lines_count;
            while (res != end && cmpStrWithData(&str, res) == 0) {
                printf("%s %s\n", (*res)->key,(*res)->value);
                ++res;
            }
        }
        free(str);
    }
    
    /*
    if (is_reverse_sorted) {
        vectorReverse(&vtable);
    }
    else if (!is_reverse_sorted && !is_sorted) {
        qsort(table,vectorCapacity(&vtable),sizeof(Data *), cmpData);
    }

    for (size_t i=0;i < vectorSize(&vtable);++i){
        printf("%s %s\n",table[i]->key,table[i]->value);
    }
    for (;;) {
        str = inputString(stdin);
        if (!str) break;
        Data **ptr = binarySearch(str,table,vectorSize(&vtable),sizeof(Data*),cmpData);
        if (!ptr) {printf("not found\n");}
        else {
            printf("%s %s\n",(*ptr)->key,(*ptr)->value);
        }
        free(str);
    }
    */
    vectorDestroy(&vtable);
    
    return 0;
}
