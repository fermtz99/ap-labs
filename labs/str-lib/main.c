#include <stdio.h>

int mystrlen(char *str);
char* mystradd(char *origin, char *addition);
int mystrfind(char *origin, char *substr);

int main(int argc, char **argv) {
    char* str = argv[1];
    int len = mystrlen(str);
    printf("Initial Lenght\t: %d\n", len);

    char* other = argv[2];
    char* newString = mystradd(str, other);
    printf("New String\t: %s\n", newString);

    char* toCompare = argv[3];
    int compared = mystrfind(newString, toCompare);
    if(compared == 1)
        printf("Substring was found : yes\n");
    else
        printf("Substring was found : no\n");
    return 0;
}
