#include <stdio.h>
#include <stdlib.h>
#include "TAD_PILHA_GENERICA.h"

typedef struct {
    int id;
    char nome[30];
} Pessoa;

int main(void) {

    Pilha *pilha = pilha_criar();
    if (pilha == NULL) {
        fprintf(stderr, "Erro ao criar a pilha.\n");
        return 1;
    }

    // exemplo com inteiros
    int a = 10, b = 20, c = 30;
    pilha_empilhar(pilha, &a);
    pilha_empilhar(pilha, &b);
    pilha_empilhar(pilha, &c);

    printf("Tamanho da pilha: %zu\n", pilha_tamanho(pilha));
    printf("Topo da pilha: %d\n", *(int *) pilha_topo(pilha));

    while (!pilha_vazia(pilha)) {
        int *valor = (int *) pilha_desempilhar(pilha);
        printf("Desempilhado: %d\n", *valor);
    }

    // exemplo com alocação dinamica
    Pessoa *p1 = malloc(sizeof(Pessoa));
    p1->id = 1;
    snprintf(p1->nome, sizeof(p1->nome), "Ana");

    Pessoa *p2 = malloc(sizeof(Pessoa));
    p2->id = 2;
    snprintf(p2->nome, sizeof(p2->nome), "Bruno");

    pilha_empilhar(pilha, p1);
    pilha_empilhar(pilha, p2);

    Pessoa *topo = (Pessoa *) pilha_topo(pilha);
    printf("\nPessoa no topo da pilha: %d - %s\n", topo->id, topo->nome);

    pilha_destruir(pilha, free);

    return 0;
}