// Fernando Martinez A01630401
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printArray(void *A[], int len) {
    int i;
    for(i = 0; i < len; i++)
        printf("%s ", A[i]);
    printf("\n");
}

void merge(void *B[], int left, int mid, int right, int (*comp) (void*, void*)) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    void *leftArray[n1], *rightArray[n2];

    for(i = 0; i < n1; i++)
        leftArray[i] = B[left + i];
    for(j = 0; j < n2; j++)
        rightArray[j] = B[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while(i < n1 && j < n2) {
        if(comp(leftArray[i], rightArray[j]) < 1 || comp(leftArray[i], rightArray[j]) == 0) {
            B[k] = leftArray[i];
            i++;
        }
        else {
            B[k] = rightArray[j];
            j++;
        }
        k++;
    }
    while(i < n1) {
        B[k] = leftArray[i];
        i++;
        k++;
    }
    while(j < n2) {
        B[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSort(void *C[], int left, int right, int (*comp)(void*, void*)) {
    if(left < right) {
        int mid = left + (right-left) / 2;

        mergeSort(C, left, mid, comp);
        mergeSort(C, mid+1, right, comp);

        merge(C, left, mid, right, comp);
    }
}

int numcmp(char *num1, char *num2) {
    double n1, n2;
    n1 = atof(num1);
    n2 = atof(num2);
    if(n1 < n2)
        return -1;
    else if(n1 > n2)
        return 1;
    else
        return 0;
}

int main(int argc, char **argv) {

    char *nums[] = {"4", "2", "9", "7", "3", "5"};
    char *words[] = {"Cama", "TV", "Reloj", "Comida", "Funcion", "Pan"};
    int len = 6;

    if(argc > 1 && strcmp(argv[1], "-n") == 0) {
        printArray(nums, len);
        mergeSort(nums, 0, len-1, numcmp);
        printArray(nums, len);
    }
    else {
        printArray(words, len);
        mergeSort(words, 0, len-1, strcmp);
        printArray(words, len);
    }
    return 0;
}
