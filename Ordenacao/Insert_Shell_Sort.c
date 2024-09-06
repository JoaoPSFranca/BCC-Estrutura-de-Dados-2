#include <stdio.h>
#include <stdlib.h>

void shell_sort(int array[], int length){
    int 
        gap = 1,
        j, tmp;

    // Acha o gap inicial com base na sequencia estranha de Knuth 
    while (gap < length)
        gap = 3 * gap + 1;
 
    // Roda a ordenação até o gap ser menor ou igual a 0
    while (gap > 0) {
        // Roda a ordenação para cada gap
        for (int i = gap; i < length; i += gap) {
            j = i;
            tmp = array[i];
 
            //
            while ((j >= gap) && (tmp < array[j - gap])) {
                array[j] = array[j - gap];
                j -= gap;
            }
 
            array[j] = tmp;
        }
        
        gap /= 3; 
    }
}

// Vai comparando os números e jogando os menores pra trás
// roda o vetor 1 vez só para frente
// e a cada número vai verificando se o número é menor que o anterior
void insertionSort(int vet[], int n) {
    int i, key, j;

    for (i = 1; i < n; ++i) {
        key = vet[i];
        j = i - 1;

        while (j >= 0 && vet[j] > key) {
            vet[j + 1] = vet[j];
            j = j - 1;
        }
        vet[j + 1] = key;
    }
}

int main(){

    int gap = 1, length = 500;

    while (gap < length) {
        gap = 3 * gap + 1;
    }

    gap /= 3;

    printf("%d", gap);

    return 0;
}