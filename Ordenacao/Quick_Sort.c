#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int part(int v[], int start, int end){
    int p, ip, i;

    p = v[end];
    ip = start;

    for (i = start; i < end; i++) {
        if (v[i] <= p){
            swap(&v[i], &v[ip]);
            ip++;
        }
    }

    swap(&v[ip], &v[end]);
    
    return ip;
}

int part_random(int v[], int start, int end){
    int i = (rand() % (end - start + 1)) + start;

    swap(&v[i], &v[end]);

    return part(v, start, end);
}

void quick_sort(int v[], int start, int end){
    if (start < end) {
        int ip = part_random(v, start, end);
        
        quick_sort(v, start, ip - 1);
        quick_sort(v, ip + 1, end);
    }
}

int main(){
    srand(time(NULL));
    int v[MAX], i;

    for (i = 0; i < MAX; i++)
        v[i] = rand() % 10 + 1;
    
    printf("Vetor original: ");
    for (i = 0; i < MAX; i++)
        printf("[%d] ", v[i]);
    
    printf("\n");
    quick_sort(v, 0, MAX);

    printf("Vetor ordenado: ");
    for (i = 0; i < MAX; i++)
        printf("[%d] ", v[i]);

    return 0;
}