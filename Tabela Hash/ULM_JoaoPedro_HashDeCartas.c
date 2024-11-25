/* Arquivo referente a versão em C do aplicativo de gerenciamento
do ULM (Ultimante League Manager) com Tabela Hash.

O ULM se trata de um programa que simula um jogo de cartas de
jogadores profissionais de League of Legends, similar ao 
funcionamento do cartola, porém de forma mais complexa e com 
mais recursos.

Cada carta possui código, nome do jogador, nota (de 0 a 100) e
valor de mercado.

O código será único para cada carta, sendo formado por até 5 
caracteres alfanuméricos (pode ser menos).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMCOD 5
#define TABLE_SIZE 11

typedef struct Carta {
    char codigo[TAMCOD + 1]; 
    char nome_jogador[50];
    int nota;
    float valor_mercado;
    struct Carta *prox;
} Carta;

// Tabela hash
Carta *tabela[TABLE_SIZE];

unsigned int hash(char *codigo) {
    unsigned int valor = 0;
    for (int i = 0; codigo[i] != '\0'; i++) {
        valor = valor * 31 + codigo[i];
    }
    return valor % TABLE_SIZE;
}

void inicializarTabela() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        tabela[i] = NULL;
    }
}

void inserirCarta(char *codigo, char *nome_jogador, int nota, float valor_mercado) {
    unsigned int indice = hash(codigo);

    Carta *nova = (Carta *) malloc(sizeof(Carta));
    strcpy(nova->codigo, codigo);
    strcpy(nova->nome_jogador, nome_jogador);
    nova->nota = nota;
    nova->valor_mercado = valor_mercado;
    nova->prox = NULL;

    if (tabela[indice] == NULL) {
        tabela[indice] = nova;
    } else {
        nova->prox = tabela[indice];
        tabela[indice] = nova;
    }
}

Carta *buscarCarta(char *codigo) {
    unsigned int indice = hash(codigo);
    Carta *atual = tabela[indice];

    while (atual != NULL) {
        if (strcmp(atual->codigo, codigo) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void removerCarta(const char *codigo) {
    unsigned int indice = hash(codigo);
    Carta *atual = tabela[indice];
    Carta *anterior = NULL;

    while (atual != NULL && strcmp(atual->codigo, codigo) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL)
        printf("Carta com codigo %s nao encontrada.\n", codigo);
    else{
        if (anterior == NULL)
            tabela[indice] = atual->prox;
        else
            anterior->prox = atual->prox;

        free(atual);
        printf("Carta com codigo %s removida.\n", codigo);
    }
}

void exibirCartas() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Carta *atual = tabela[i];
        if (atual != NULL) {
            printf("Indice %d:\n", i);
            while (atual != NULL) {
                printf("  Codigo: %s, Jogador: %s, Nota: %d, Valor: %.2f\n", 
                        atual->codigo, atual->nome_jogador, atual->nota, atual->valor_mercado);
                atual = atual->prox;
            }
        }
    }
}

void getCodigo(char codigo[]){
    fflush(stdin);
    printf("Digite o codigo da carta (ate 5 caracteres): ");
    fgets(codigo, sizeof(codigo), stdin);
    codigo[strcspn(codigo, "\n")] = '\0';
}

void getNome(char nome[]){
    fflush(stdin);
    printf("Digite o nome do jogador: ");
    fgets(nome, sizeof(nome), stdin);
}

void getNota(int *nota){
    fflush(stdin);
    printf("Digite a nota do jogador (0 a 100): ");
    scanf("%d", nota);
    getchar();
}

void getValor(float *valor_mercado){
    fflush(stdin);
    printf("Digite o valor de mercado da carta: ");
    scanf("%f", valor_mercado);
    getchar();
}

void exibirMenu() {
    printf("\n--- Gerenciamento de Cartas ULM ---\n");
    printf("1. Inserir nova carta\n");
    printf("2. Buscar carta\n");
    printf("3. Remover carta\n");
    printf("4. Exibir todas as cartas\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    inicializarTabela();

    inicializarTabela();
    int opcao;
    char codigo[6], nome_jogador[50];
    int nota;
    float valor_mercado;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 0: // Sair
                printf("Saindo do programa...\n");
                break;

            case 1: // Inserir Carta
                getCodigo(codigo);
                getNome(nome_jogador);
                getNota(&nota);
                getValor(&valor_mercado);

                inserirCarta(codigo, nome_jogador, nota, valor_mercado);
                printf("Carta inserida com sucesso!\n");
                break;

            case 2: // Buscar carta
                getCodigo(codigo);

                Carta *c = buscarCarta(codigo);
                if (c != NULL) {
                    printf("Carta encontrada: %s, Jogador: %s, Nota: %d, Valor: %.2f\n", 
                            c->codigo, c->nome_jogador, c->nota, c->valor_mercado);
                } else {
                    printf("Carta nao encontrada.\n");
                }
                break;

            case 3: // Remover carta
                getCodigo(codigo);

                removerCarta(codigo);
                break;

            case 4: // Exibir todas as cartas
                printf("\nCartas na tabela hash:\n");
                exibirCartas();
                break;

            default:
                printf("Opçao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
