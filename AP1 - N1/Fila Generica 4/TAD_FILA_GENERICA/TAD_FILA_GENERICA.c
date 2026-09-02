#include "TAD_FILA_GENERICA.h"
#include <stdlib.h>

typedef struct No {
    void *dado;
    struct No *proximo;
} No;

struct Fila {
    No *inicio;
    No *fim;
    size_t tamanho;
};

Fila *fila_criar(void) {

    Fila *fila = (Fila *) malloc(sizeof(Fila));
    if (fila == NULL) {
        return NULL;
    }

    fila->inicio = NULL; // nada na fila ainda
    fila->fim = NULL;
    fila->tamanho = 0;

    return fila;
}

void fila_destruir(Fila *fila, void (*liberar_dado)(void *dado)) {

    if (fila == NULL) {
        return;
    }

    No *atual = fila->inicio;
    while (atual != NULL) {
        No *proximo = atual->proximo;

        if (liberar_dado != NULL) {
            liberar_dado(atual->dado);
        }

        free(atual);
        atual = proximo;
    }

    free(fila);
}

int fila_enfileirar(Fila *fila, void *dado) {

    if (fila == NULL) {
        return 0;
    }

    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) {
        return 0;
    }

    novo->dado = dado;
    novo->proximo = NULL;

    if (fila->fim == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->proximo = novo;
        fila->fim = novo;
    }

    fila->tamanho++;
    return 1;
}

void *fila_desenfileirar(Fila *fila) {

    if (fila == NULL || fila->inicio == NULL) {
        return NULL;
    }

    No *removido = fila->inicio;
    void *dado = removido->dado;

    fila->inicio = removido->proximo;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(removido);
    fila->tamanho--;

    return dado;
}

void *fila_frente(Fila *fila) {

    if (fila == NULL || fila->inicio == NULL) {
        return NULL;
    }
    return fila->inicio->dado;
}

int fila_vazia(const Fila *fila) {
    
    return (fila == NULL || fila->tamanho == 0);
}

size_t fila_tamanho(const Fila *fila) {
    if (fila == NULL) {
        return 0;
    }
    return fila->tamanho;
}