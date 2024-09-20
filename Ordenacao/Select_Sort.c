#include <stdio.h>
#include <stdlib.h>
#define MAX 10

// Vai rodando o vetor inteiro e procurando o menor depois coloca na posição mais baixa
void select_sort(int v[]){
    int i, aux, pos, start = 0;

    while (start != MAX) {
        pos = start;

        for (i = start; i < MAX; i++)
            if (v[i] < v[pos])
                pos = i;
        
        if (pos != start){
            aux = v[start];
            v[start] = v[pos];
            v[pos] = aux;
        }

        start++;
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
    select_sort(v);

    printf("Vetor ordenado: ");
    for (i = 0; i < MAX; i++)
        printf("[%d] ", v[i]);

    return 0;
}