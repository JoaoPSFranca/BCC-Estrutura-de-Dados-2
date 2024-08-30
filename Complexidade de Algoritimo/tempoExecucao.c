#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define tam1 10000 // 344 - 6 min
#define tam2 20000 // 2519 - 41 min

int conta(int *a, int n){
    int cont = 0; 
    int i, j, k;

    for(i = 0; i < n; i++)
        for(j = i + 1; j < n; j++)
            for(k = j + 1; k < n; k++)
                if(a[i] + a[j] + a[k] == 0)
                    cont++;

    return cont;
}

int main(){
    int va[tam1];
    int vb[tam2];
    int i;
    clock_t tempo10;
    clock_t tempo20;

    srand(time(NULL));

    for (i = 0; i < tam1; i++)
        va[i] = rand() % ((-100) - 100 + 1) + (-100); 
    
    for (i = 0; i < tam2; i++)
        vb[i] = rand() % ((-100) - 100 + 1) + (-100); 

    tempo10 = clock();
    conta(va, tam1);
    tempo10 = clock() - tempo10;

    printf("Tempo de %d: %.2lf", tam1, ((double) tempo10 / CLOCKS_PER_SEC));
    
    tempo20 = clock();
    conta(vb, tam2);
    tempo20 = clock() - tempo20;

    printf("\nTempo de %d: %2.lf", tam2, ((double) tempo20 / CLOCKS_PER_SEC));

    return 0;
}