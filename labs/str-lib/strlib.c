#include <stdlib.h>

int mystrlen(char *str){
    int i;
    for(i = 0; str[i]; i++);
    return i;
}

char *mystradd(char *origin, char *addition){
    int len1 = mystrlen(origin);
    int len2 = mystrlen(addition);
    char *stradded = malloc(len1+len2+1);
    int i;
    for(i = 0; i < len1; i++) {
        stradded[i] = origin[i];
    }
    int e;
    for(e = 0; e < len2; e++) {
        stradded[i++] = addition[e];
    }
    return stradded;
}

int mystrfind(char *origin, char *substr){
    int len1 = mystrlen(origin);
    int len2 = mystrlen(substr);
    int i;
    int e;
    for(i = 0; i < len1; i++) {
        if(origin[i] == substr[0]) {
            for(e = 0; e < len2; e++) {
                if(origin[i+e] != substr[e])
                    break;
            }
            if(e == len2)
                return 1;
        }
    }
    return 0;
}
