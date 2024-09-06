#include <stdio.h>
#include <stdlib.h>
#define MAX 5

void readVet(int *vet){
    int i;

    for (i = 0; i < MAX; i++){
        printf("Informe o numero: ");
        scanf("%d", &vet[i]);
    }
}

void swap(int *a, int *b){ 
    int temp = *a; 
    *a = *b; 
    *b = temp; 
}

// Vai jogando o maior sempre pro final
void bubbleSort(int *vet, int max, int *contador){ 
    if (max < 1) return; 
    
    int i;

    for (i = 0; i < max; i++) {
        (*contador)++;
        if (vet[i] > vet[i+1]) 
            swap(&vet[i], &vet[i+1]);
    }
    
    bubbleSort(vet, max-1, contador); 
}

// Vai rodando o vetor inteiro e procurando o menor depois colocando na posição mais baixa
void selection_sort(int *vet, int max, int *contador) { 
    int i, j, min, aux;
    
    for (i = 0; i < max; i++) {
        (*contador)++;     
        min = i;
        for (j = (i+1); j < max; j++)
            if(vet[j] < vet[min]) 
                min = j;
        if (i != min) {
            aux = vet[i];
            vet[i] = vet[min];
            vet[min] = aux;
        }
    }
}

int buscaSequencial(int elem, int *vet, int *cont) {
    int i=0;

    while (elem > vet[i] && i < MAX){
        (*cont)++;
        i=i+1;
    }

    if (i < MAX && elem == vet[i])
        return i;
    else 
        return -1;
}

int buscaBinaria(int chave, int *vet, int *cont) {
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

    return -1;
}

void show(int *vet){
    int i = 0;
    
    printf("Numeros no vetor: ");

    for (i = 0; i < MAX; i++){
        printf("%d ", vet[i]);
    }
}

void copyVet(int *vet, int *vetCopy){
    for (int i = 0; i < MAX; i++)
        vetCopy[i] = vet[i];
}

int menu(){
    int opcao;

    printf( "\n1 - Ler vetor; \n"
            "2 - Ordenar vetor por Buble-Sort; \n"
            "3 - Ordenar vetor por Select-Sort; \n"
            "4 - Realizar Busca Sequencial; \n"
            "5 - Realizar Busca Binária; \n"
            "6 - Mostrar vetor; \n"
            "0 - Sair do programa; \n");

    printf("\nEscolha uma opcao: ");
    scanf("%d", &opcao);

    return opcao;
}

int main(){
    int vet[MAX];
    int vetCopy[MAX];
    int contBubble = 0;
    int contSelect = 0;
    int contBuscaSequencial = 0;
    int contBuscaBinaria = 0;
    int opcao;
    int elem;
    int pos;

    do {
        opcao = menu();

        switch (opcao) {
            case 0:
                break;
            case 1:
                readVet(vet);
                break;
            case 2:
                contBubble = 0;
                copyVet(vet, vetCopy);
                bubbleSort(vetCopy, MAX, &contBubble);
                printf("Vetor ordenado por Bubble-Sort teve %d comparacoes\n", contBubble);
                break;
            case 3:
                contSelect = 0;
                copyVet(vet, vetCopy);
                selection_sort(vetCopy, MAX, &contSelect);
                printf("Vetor ordenado por Select-Sort teve %d comparacoes\n", contSelect);
                break;
            case 4:
                contBuscaSequencial = 0;
                printf("Informe o elemento a ser buscado: ");
                scanf("%d", &elem);
                pos = buscaSequencial(elem, vetCopy, &contBuscaSequencial);
                if (pos != -1) {
                    printf("Elemento encontrado na posicao %d com %d comparacoes\n", pos, contBuscaSequencial);
                } else {
                    printf("Elemento nao encontrado com %d comparacoes\n", contBuscaSequencial);
                }
                break;
            case 5:
                contBuscaBinaria = 0;
                printf("Informe o elemento a ser buscado: ");
                scanf("%d", &elem);
                pos = buscaBinaria(elem, vetCopy, &contBuscaBinaria);
                if (pos != -1) {
                    printf("Elemento encontrado na posicao %d com %d comparacoes\n", pos, contBuscaBinaria);
                } else {
                    printf("Elemento nao encontrado com %d comparações\n", contBuscaBinaria);
                }
                break;
            case 6:
                printf("\nOriginal: \n");
                show(vet);
                printf("\nOrdenado: \n");
                show(vetCopy);
                printf("\n");
                break;
            default:
                printf("Opção invalida\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}