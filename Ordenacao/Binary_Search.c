#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10

int binary_search(int v[], int k){
    int start = 0, end = MAX - 1, middle;

    while (start <= end) {
        middle = (start + end)/2;

        if (v[middle] == k)
            return middle;
        
        if (v[middle] > k)
            start = middle + 1;
        else
            end = middle - 1;
    }

    return -1;
}