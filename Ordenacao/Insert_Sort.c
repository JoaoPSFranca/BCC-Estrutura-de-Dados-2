#include <stdio.h>
#include <stdlib.h>
#define MAX 10

void insert_sort(int v[]){
    int i, j, aux;

    for (i = 1; i < MAX; i++){
        aux = v[i];
        j = i - 1;

        while(j >= 0 && v[j] > aux){
            v[j+1] = v[j];
            j--;
        }

        v[j+1] = aux;
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
    insert_sort(v);

    printf("Vetor ordenado: ");
    for (i = 0; i < MAX; i++)
        printf("[%d] ", v[i]);

    return 0;
}