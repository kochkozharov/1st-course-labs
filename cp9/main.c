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
    for (size_t i=0;i < lines_count;++i){
        printf("%s %s\n",table[i]->key,table[i]->value);
    }
    printf("---------\n");
    #if (1) //1 is stable, 0 is unstable but faster in some cases
    mergeSort(table,lines_count,sizeof(Data*),cmpData);
    #else
    int asc=1, desc = 1;
    for (size_t i=0;(asc == 1 || desc == 1) && i < lines_count - 1;++i) {
        if (cmpData(&table[i],&table[i+1])<0) desc = 0;
        else if (cmpData(&table[i],&table[i+1])>0) asc = 0;
    }

    if (desc) {
        reverse(table,lines_count,sizeof(Data*));
    }
    else if (asc == 0 && desc == 0) {
        mergeSort(table,lines_count,sizeof(Data*),cmpData);
    }
    #endif
    
    for (size_t i=0;i < lines_count;++i){
        printf("%s %s\n",table[i]->key,table[i]->value);
    }
    /* tests 
    printf("%s\n",(*(Data**)upperBound(&(char*){"a"},table,lines_count,sizeof(Data*),cmpData))->value);
    Pair res = equalRange(&(char*){"a"},table,lines_count,sizeof(Data*),cmpData);
    printf("%s, %s\n",(*(Data**)res.first)->value,(*(Data**)res.second)->value);
    */
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
    vectorDestroy(&vtable);
    return 0;
}
