// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5   // Tamanho fixo da fila

// Struct que representa uma peça
typedef struct {
    char nome;  
    int id;      
    
} Peca;
// Fila circular para armazenar as peças
typedef struct {
    Peca itens[TAMANHO_FILA];
    int frente;
    int tras;
    int quantidade;
} Fila;

//  PROTÓTIPOS
void inicializarFila(Fila *fila);
int filaCheia(Fila *fila);
int filaVazia(Fila *fila);

Peca gerarPeca();
void enqueue(Fila *fila, Peca nova);
void dequeue(Fila *fila);

void exibirFila(Fila *fila);

int main() {
    Fila fila;
    int opcao;
    int proximoID = 0;  // ID crescente para cada peça gerada

    srand(time(NULL));  // gerar peças aleatórias

    inicializarFila(&fila);

    // Preenche a fila com 5 peças iniciais
    for (int i = 0; i < TAMANHO_FILA; i++) {
        Peca p = gerarPeca();
        p.id = proximoID++;
        enqueue(&fila, p);
    }

    do {
        printf("\n========================\n");
        printf("     FILA DE PEÇAS\n");
        printf("========================\n");
        exibirFila(&fila);

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                dequeue(&fila);
                break;

            case 2: {
                if (!filaCheia(&fila)) {
                    Peca nova = gerarPeca();
                    nova.id = proximoID++;
                    enqueue(&fila, nova);
                } else {
                    printf("\nA fila está cheia! Não é possível inserir.\n");
                }
                break;
            }

            case 0:
                printf("\nEncerrando o programa...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// Inicializa a fila circular
void inicializarFila(Fila *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->quantidade = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *fila) {
    return fila->quantidade == TAMANHO_FILA;
}

// Verifica se a fila está vazia
int filaVazia(Fila *fila) {
    return fila->quantidade == 0;
}

// Insere peça no final
void enqueue(Fila *fila, Peca nova) {
    if (filaCheia(fila)) {
        printf("\nErro: fila cheia, não é possível inserir!\n");
        return;
    }

    fila->tras = (fila->tras + 1) % TAMANHO_FILA;
    fila->itens[fila->tras] = nova;
    fila->quantidade++;

    printf("\nPeça [%c %d] inserida na fila.\n", nova.nome, nova.id);
}

// Remove peça do início
void dequeue(Fila *fila) {
    if (filaVazia(fila)) {
        printf("\nErro: fila vazia, não há peças para jogar!\n");
        return;
    }

    Peca removida = fila->itens[fila->frente];
    fila->frente = (fila->frente + 1) % TAMANHO_FILA;
    fila->quantidade--;

    printf("\nPeça jogada: [%c %d]\n", removida.nome, removida.id);
}
// GERAÇÃO AUTOMÁTICA DE PEÇAS
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca p;
    p.nome = tipos[rand() % 4];  // Escolhe aleatório
    
    return p;
}
// EXIBE A FILA COMPLETA
void exibirFila(Fila *fila) {
    if (filaVazia(fila)) {
        printf("\nFila vazia!\n");
        return;
    }

    printf("\nFila de Peças:\n");

    int i = fila->frente;

    for (int c = 0; c < fila->quantidade; c++) {
        Peca p = fila->itens[i];
        printf("[%c %d] ", p.nome, p.id);
        i = (i + 1) % TAMANHO_FILA;
    }

    printf("\n");
}


