#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10000

int buscaSequencial(int elem, int vetor[], int *cont) {
    int i=0;

    while (elem > vetor[i] && i < MAX){
        (*cont)++;
        i=i+1;
    }

    if (i < MAX && elem == vetor[i])
        return i; // achou na posição i
    else 
        return -1; // não achou
}

int buscaBinaria(int chave, int vet[], int *cont) {
    int inicio = 0;
    int fim = MAX-1;
    int meio;

    while (inicio <= fim) {
        (*cont)++;
        meio = (inicio + fim)/2;
        
        if (chave == vet[meio])
            return meio;
        
        if (chave < vet[meio])
            fim = meio-1;
        else
            inicio = meio+1;
    }
    return -1; // não encontrado
}

int main(){
    int ordenado[MAX];
    int i;
    clock_t tempo;
    int cont;

    srand(time(NULL));

    tempo = clock();
    for (i = 0; i < MAX; i++) {
        ordenado[i] = i+1;
    }
    tempo = clock() - tempo;
    printf("Preencher vetor ordenado: %.2lf", ((double) tempo/CLOCKS_PER_SEC));

    int valor = rand() % 10000;
    int posicao = 0;

    tempo = clock();
    posicao = buscaSequencial(valor, ordenado, &cont);
    tempo = clock() - tempo;
    printf("\n\nTempo de busca sequencial vetor ordenado: %.2lf", ((double) tempo/CLOCKS_PER_SEC));
    printf("\nPosicao: %d | Valor: %d | Passos: %d", posicao, valor, cont);

    cont = 0;
    tempo = clock();
    posicao = buscaBinaria(valor, ordenado, &cont);
    tempo = clock() - tempo;
    printf("\n\nTempo de busca Binaria vetor ordenado: %.2lf", ((double) tempo/CLOCKS_PER_SEC));
    printf("\nPosicao: %d | Valor: %d | Passos: %d", posicao, valor, cont);

    return 0;
}
