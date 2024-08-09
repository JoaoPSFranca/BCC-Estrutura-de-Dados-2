#include <stdio.h>
#include <stdlib.h>

typedef struct sStack{
    int info;
    struct sStack *next;
} STACK;

typedef struct sList{
    int info;
    struct sList *next;
    struct sList *back;
} LIST;

typedef struct sQueue{
    int info;
    struct sQueue *next;
} QUEUE;

int getInfo(){
    int info;
    
    printf("Qual a placa do carro? (somente numeros) \n");
    scanf("%d", &info);

    return info;
}

int menuTipo(){
    int opt;

    printf("Qual a tecnica a ser utilizada? \n");
    printf("1. Pilha \n");
    printf("2. Fila \n");
    printf("3. Lista \n");
    printf("0. Sair \n");
    printf("Sua escolha: ");
    scanf("%d", &opt);

    return opt;
}

int menuGeral(){
    int opt;

    printf("O que deseja fazer? \n");
    printf("1. Estacionar o carro \n");
    printf("2. Retirar o carro \n");
    printf("3. Olhar o carro \n");
    printf("0. Voltar \n");
    printf("Sua escolha: ");
    scanf("%d", &opt);

    return opt;
}

void pushStack(STACK **root, int info){
    STACK *newNode = (STACK *) malloc(sizeof(STACK)); 
    newNode->info = info;

    if (*root == NULL)
        newNode->next = NULL;
    else 
        newNode->next = *root;
    
    *root = newNode;
}

int popStack(STACK **root){
    int info = 0;

    if (*root == NULL) { return 0; }
    
    info = (*root)->info;

    STACK *aux = *root;
    *root = (*root)->next;
    (*root)->next = NULL;
    free(aux);

    return info;
}

int findCarStack(STACK **root, int info, int action){
    STACK *aux = *root;
    int finded;
    
    while(*root != NULL && (*root)->info != info){
        pushStack(&aux, popStack(root));
    }

    if (*root != NULL){
        switch (action){
            case 1:
                finded = 1;
                break;
            case 2:
                finded = popStack(root);
                break;
        }
    } else { finded = 0; }
    

    while(*root != NULL && (*root)->info != info){
        pushStack(&root, popStack(aux));
    }

    return finded;
}

void switchStack(){
    int opt = 10;
    STACK *root = (STACK *) malloc(sizeof(STACK));

    while (opt != 0) {
        opt = menuGeral();
        
        switch (opt){
            case 0:
                break;
            
            case 1:
                int info = getInfo();
                pushStack(&root, info);
                break;

            case 2:
                if (root == NULL) { printf("Estacionamento vazio!\n"); }
                else {
                    int info = getInfo();
                    info = findCarStack(&root, info, 1);
                    
                    if (info == 0)
                        printf("Carro nao encontrado!\n");
                    else
                        prixntf("Carro removido: %d\n", info);
                }
                break;

            case 3:
                if (root == NULL) { printf("Estacionamento vazio!\n"); }
                else {
                    int info = getInfo();
                    info = findCarStack(&root, info, 2);
                    
                    if (info == 0)
                        printf("Carro nao encontrado! \n");
                    else
                        prixntf("Carro encontrado! \n");
                }
                break;

            default:
                printf("Opcao invalida. \n");
                break;
        }
    }
}

int main(){
    int type = 10;

    while (type != 0) {
        type = menuTipo();

        switch (type) {
            case 0:
                break;

            case 1: // stack
                switchStack();
                break;

            case 2: // Queue
                switchQueue();
                break;

            default:  
                printf("Opcao invalida. \n");
                break;
        }
    }
    
}
