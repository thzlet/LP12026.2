#include <stdio.h>
#include <stdlib.h>
#include "TAD_LISTA_FILMES.h"

Lista* criarLista(void) {

    Lista *lista = (Lista*) malloc(sizeof(Lista)); // se esquecer de alocar é baguga total

    if (lista == NULL) {
        printf("Erro na alocacao da lista!\n");
        return NULL;
    }

    lista->inicio = NULL; // lista ta vazia 
    lista->tamanho = 0;

    return lista;
}

int listaVazia(Lista *lista) {

    if (lista == NULL) {
        return 1;
    }
    return lista->inicio == NULL;
}

int inserirInicio(Lista *lista, void *dado) {

    No *novo;

    if (lista == NULL || dado == NULL) {
        return 0;
    }
    novo = (No*) malloc(sizeof(No));

    if (novo == NULL) {
        return 0;
    }
    novo->dado = dado;
    novo->prox = lista->inicio;

    lista->inicio = novo;
    lista->tamanho++;

    return 1;
}

int inserirFim(Lista *lista, void *dado) {
    No *novo;
    No *atual;

    if (lista == NULL || dado == NULL) {
        return 0;
    }
    novo = (No*) malloc(sizeof(No));

    if (novo == NULL) {
        return 0;
    }
    novo->dado = dado;
    novo->prox = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        atual = lista->inicio;

        while (atual->prox != NULL) {
            atual = atual->prox;
        }

        atual->prox = novo;
    }

    lista->tamanho++;

    return 1;
}

void* removerInicio(Lista *lista) {

    No *aux;
    void *dado;

    if (lista == NULL || lista->inicio == NULL) {
        return NULL;
    }
    aux = lista->inicio;
    dado = aux->dado;

    lista->inicio = aux->prox;

    free(aux);

    lista->tamanho--;

    return dado;
}

void* removerFim(Lista *lista) {

    No *atual;
    No *anterior;
    void *dado;

    if (lista == NULL || lista->inicio == NULL) {
        return NULL;
    }
    atual = lista->inicio;
    anterior = NULL;

    while (atual->prox != NULL) {
        anterior = atual;
        atual = atual->prox;
    }
    dado = atual->dado;

    if (anterior == NULL) {
        lista->inicio = NULL;
    } else {
        anterior->prox = NULL;
    }

    free(atual);

    lista->tamanho--;
    return dado;
}

void imprimirLista(Lista *lista, void (*imprimir)(void *)) {

    No *atual;

    if (lista == NULL || imprimir == NULL) {
        return;
    }
    atual = lista->inicio;

    while (atual != NULL) {
        imprimir(atual->dado);
        atual = atual->prox;
    }
}

void liberarLista(Lista *lista, void (*liberar)(void *)) {

    No *atual;
    No *aux;

    if (lista == NULL) {
        return;
    }
    atual = lista->inicio;

    while (atual != NULL) {
        aux = atual->prox;

        if (liberar != NULL) {
            liberar(atual->dado);
        }
        free(atual);

        atual = aux;
    }

    free(lista);
}

void percorrerLista(Lista *lista, void (*processa)(void *)) {

    No *atual;
    if (lista == NULL || processa == NULL) {
        return;
    }
    atual = lista->inicio;

    while (atual != NULL) {
        processa(atual->dado);
        atual = atual->prox;
    }
}

void* buscarLista(Lista *lista, int (*compara)(void *, void *), void *dado) {
    No *atual;
    if (lista == NULL || compara == NULL) {
        return NULL;
    }
    atual = lista->inicio;

    while (atual != NULL) {
        if (compara(atual->dado, dado) == 0) {
            return atual->dado;
        }
        atual = atual->prox;
    }

    return NULL;
}

void* retirarLista(Lista *lista, int (*compara)(void *, void *), void *dado) {

    No *atual;
    No *anterior;
    void *elemento;

    if (lista == NULL || lista->inicio == NULL || compara == NULL) {
        return NULL;
    }
    atual = lista->inicio;
    anterior = NULL;

    while (atual != NULL) {
        if (compara(atual->dado, dado) == 0) {
            if (anterior == NULL) {
                lista->inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            elemento = atual->dado;

            free(atual);

            lista->tamanho--;

            return elemento;
        }

        anterior = atual;
        atual = atual->prox;
    }

    return NULL;
}

Lista* duplicarLista(Lista *lista, void* (*duplica)(void *)) {

    Lista *nova;
    No *atual;

    if (lista == NULL || duplica == NULL) {
        return NULL;
    }
    nova = criarLista();

    if (nova == NULL) {
        return NULL;
    }    
    atual = lista->inicio;

    while (atual != NULL) {
        void *novoDado = duplica(atual->dado);

        if (novoDado == NULL) {
            liberarLista(nova, free);
            return NULL;
        }

        inserirFim(nova, novoDado);

        atual = atual->prox;
    }

    return nova;
}

Lista* filtrarLista(Lista *lista, int (*criterio)(void *)) {

    Lista *nova;
    No *atual;

    if (lista == NULL || criterio == NULL) {
        return NULL;
    }
    nova = criarLista();

    if (nova == NULL) {
        return NULL;
    }
    atual = lista->inicio;

    while (atual != NULL) {
        if (criterio(atual->dado)) {
            inserirFim(nova, atual->dado);
        }
        atual = atual->prox;
    }
    return nova;
}

Lista* ordenarLista(Lista *lista, int (*compara)(void *, void *)) { 

    No *i;
    No *j;
    void *aux;

    if (lista == NULL || compara == NULL) {
        return lista;
    }
    for (i = lista->inicio; i != NULL; i = i->prox) {
        for (j = i->prox; j != NULL; j = j->prox) {
            if (compara(i->dado, j->dado) > 0) {
                aux = i->dado;
                i->dado = j->dado;
                j->dado = aux;
            }
        }
    }

    return lista;
}