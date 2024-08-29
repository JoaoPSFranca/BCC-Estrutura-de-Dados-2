#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 519273


int maximo(int v[]){
    int max = v[0];

    for(int i = 1; i < TAM; i++)
        if(max < v[i])
            max = v[i];

    return max;    
}

int main(){
    int i;
    int v[TAM];
    clock_t tempo;

    srand(time(NULL));

    tempo = clock();

    for (i = 0; i < TAM; i++)
        v[i] = rand() % 10000; 

    tempo = clock() - tempo;
    printf("Tempo de preenchimento: %.5lf", ((double) tempo / CLOCKS_PER_SEC));
    
    tempo = clock();

    int max = maximo(v);

    tempo = clock() - tempo;
    printf("\nTempo de busca: %.5lf", ((double) tempo / CLOCKS_PER_SEC));
    printf("\nO maior valor encontrado foi: %d", max);

    return 0;
}