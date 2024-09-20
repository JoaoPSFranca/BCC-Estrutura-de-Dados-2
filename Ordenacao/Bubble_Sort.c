#include <stdio.h>
#include <stdlib.h>
#define MAX 10

// Vai jogando o maior sempre pro final
void bubble_sort(int v[]){
    int i, aux, end = MAX;

    while(end > 0){
        for (i = 0; i < end - 1; i++) {
            if (v[i] > v[i + 1]){
                aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;
            }
        }
        end--;
    }
}

int main(){
    srand(time(NULL));
    int v[MAX], i;
    
    for (i = 0; i < MAX; i++)
        v[i] = rand() % 11 + 1;
    
    printf("Vetor original: ");
    for (i = 0; i < MAX; i++)
        printf("[%d] ", v[i]);
    
    printf("\n");
    bubble_sort(v);

    printf("Vetor ordenado: ");
    for (i = 0; i < MAX; i++)
        printf("[%d] ", v[i]);

    return 0;
}