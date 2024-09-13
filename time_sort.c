#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10

typedef struct sTIMES {
    char nome;
    int pontuacao;
}TIMES;

// função que realiza a troca entre dois elementos
void troca(TIMES vet[], int i, int j) {
	int aux = vet[i].pontuacao;
    char aux2 = vet[i].nome;
    
	vet[i].pontuacao = vet[j].pontuacao;
    vet[i].nome = vet[j].nome;

	vet[j].pontuacao = aux;
    vet[j].nome = aux2;
}

// particiona e retorna o índice do pivô
int particiona(TIMES vet[], int inicio, int fim) {
	int pivo, pivo_indice, i;
	
	pivo = vet[fim].pontuacao; // o pivô é sempre o último elemento
	pivo_indice = inicio;
	
	for(i = inicio; i < fim; i++) {
		// verifica se o elemento é <= ao pivô
		if(vet[i].pontuacao <= pivo)
		{
			// realiza a troca
			troca(vet, i, pivo_indice);
			// incrementa o pivo_indice
			pivo_indice++;
		}
	}
	
	// troca o pivô
	troca(vet, pivo_indice, fim);
	
	// retorna o índice do pivô
	return pivo_indice;
}

// escolhe um pivô aleatório para evitar o pior caso do quicksort
int particiona_random(TIMES vet[], int inicio, int fim) {
	// seleciona um número entre fim (inclusive) e inicio (inclusive)
	int pivo_indice = (rand() % (fim - inicio + 1)) + inicio;
	
	// faz a troca para colocar o pivô no fim
	troca(vet, pivo_indice, fim);
	// chama a particiona
	return particiona(vet, inicio, fim);
}

void quick_sort(TIMES vet[], int inicio, int fim) {
	if(inicio < fim) {
		// função particionar retorna o índice do pivô
		int pivo_indice = particiona_random(vet, inicio, fim);
		
		// chamadas recursivas quick_sort
		quick_sort(vet, inicio, pivo_indice - 1);
		quick_sort(vet, pivo_indice + 1, fim);
	}
}

void printVetor(TIMES t[]){
    for (int i = 0; i < MAX; i++)
        printf("Time %c - %d\n", t[i].nome, t[i].pontuacao);
}

void heapsort(TIMES a[], int n) {
    int i = n / 2, pai, filho, t;
    char aux;

    while (1){
        if (i > 0) {
            i--;
            t = a[i].pontuacao;
            aux = a[i].nome;
        } else {
            n--;
            if (n <= 0)
                return;
            t = a[n].pontuacao;
            a[n].pontuacao = a[0].pontuacao;
            aux = a[n].nome;
            a[n].nome = a[0].nome;
        }

        pai = i;
        filho = i * 2 + 1;
        
        while (filho < n) {
            if ((filho + 1 < n) && (a[filho + 1].pontuacao > a[filho].pontuacao))
                filho++;
            if (a[filho].pontuacao > t) {
                a[pai].pontuacao = a[filho].pontuacao;
                a[pai].nome = a[filho].nome;
                pai = filho;
                filho = pai * 2 + 1;
            } else {
                break;
            }
        }

        a[pai].pontuacao = t;
        a[pai].nome = aux;
    }
}

void preencherVetor(TIMES t[]){
    for (int i = 0; i < MAX; i++){
        t[i].nome = 65 + i;
        t[i].pontuacao = rand() % 100 + 1;
    }
}


int main(){
    srand(time(NULL));

    TIMES q[MAX];
    TIMES h[MAX];

    preencherVetor(q);
    quick_sort(q, 0, MAX - 1);
    printf("QuickSort: \n");
    printVetor(q);

    preencherVetor(h);
    heapsort(h, MAX);
    printf("\nHeapSort: \n");
    printVetor(h);

    return 0;
}