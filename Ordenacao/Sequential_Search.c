#include <stdio.h>
#include <stdlib.h>
#define MAX 10

int sequential_search(int v[], int k){
    int i = 0;

    while (k > v[i] && i < MAX)
        i++;
    
    if (k == v[i])
        return i;
    else 
        return -1;
}