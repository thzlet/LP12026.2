#include "TAD_PILHA_GENERICA.h"
#include <stdlib.h>

typedef struct No {
    void *dado;
    struct No *proximo;
} No;

struct Pilha {
    No *topo;
    size_t tamanho;
};

Pilha *pilha_criar(void) {

    Pilha *pilha = (Pilha *) malloc(sizeof(Pilha));
    if (pilha == NULL) {
        return NULL;
    }

    pilha->topo = NULL;
    pilha->tamanho = 0;

    return pilha;
}

void pilha_destruir(Pilha *pilha, void (*liberar_dado)(void *dado)) {

    if (pilha == NULL) {
        return;
    }

    No *atual = pilha->topo;
    while (atual != NULL) {
        No *proximo = atual->proximo;

        if (liberar_dado != NULL) {
            liberar_dado(atual->dado);
        }

        free(atual);
        atual = proximo;
    }

    free(pilha);
}

int pilha_empilhar(Pilha *pilha, void *dado) {

    if (pilha == NULL) {
        return 0;
    }

    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) {
        return 0;
    }

    novo->dado = dado;
    novo->proximo = pilha->topo;
    pilha->topo = novo;

    pilha->tamanho++;
    return 1;
}

void *pilha_desempilhar(Pilha *pilha) {

    if (pilha == NULL || pilha->topo == NULL) {
        return NULL;
    }

    No *removido = pilha->topo;
    void *dado = removido->dado;

    pilha->topo = removido->proximo;

    free(removido);
    pilha->tamanho--;

    return dado;
}

void *pilha_topo(Pilha *pilha) {

    if (pilha == NULL || pilha->topo == NULL) {
        return NULL;
    }
    return pilha->topo->dado;
}

int pilha_vazia(const Pilha *pilha) {

    return (pilha == NULL || pilha->tamanho == 0);
}

size_t pilha_tamanho(const Pilha *pilha) {
    
    if (pilha == NULL) {
        return 0;
    }
    return pilha->tamanho;
}