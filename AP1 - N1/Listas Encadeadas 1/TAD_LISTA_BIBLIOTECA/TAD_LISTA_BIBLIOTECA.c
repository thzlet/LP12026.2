#include <stdio.h>
#include <stdlib.h>
#include "TAD_LISTA_BIBLIOTECA.h"

void criarLista(ListaBiblioteca *lista) {
    lista->inicio = NULL; // tem nada na lista
    lista->tamanho = 0; 
}

void inserirInicio(ListaBiblioteca *lista, Livro livro) {
    No *novo = (No *) malloc(sizeof(No)); // n pode esquecer de alocar
    if (novo == NULL) { // nem de verificar
        printf("Erro\n");
        return;
    }

    novo->dado = livro; //dado em NOVO recebe livro
    novo->prox = lista->inicio; // agora o proximo nó é o que antes era o primeiro
    lista->inicio = novo; // o inicio passa a ser o nó alocado 
    lista->tamanho++;
}

void inserirFim(ListaBiblioteca *lista, Livro livro) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro: memoria insuficiente.\n");
        return;
    }

    novo->dado = livro;
    novo->prox = NULL; // pq ta no final ne, old

    if (listaVazia(lista)) {
        lista->inicio = novo; // se tivar vazia vai no inicio mesmo 
    } else {
        No *atual = lista->inicio; // variavel auxiliar pra percorrer a lista
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo; // pafo
    }

    lista->tamanho++; // incrementa
}

void removerInicio(ListaBiblioteca *lista) {
    if (listaVazia(lista)) { // claro 
        printf("Lista vazia. Nada para remover.\n");
        return;
    }

    No *removido = lista->inicio; // variavel auxiliar pra guardar o nó que vai ser removido
    lista->inicio = removido->prox;
    free(removido);
    lista->tamanho--; // pafo
}

int listaVazia(ListaBiblioteca *lista) {
    return (lista->inicio == NULL); // besteira
}

int tamanhoLista(ListaBiblioteca *lista) {
    return lista->tamanho; // besteira
}

void imprimirLista(ListaBiblioteca *lista) {
    if (listaVazia(lista)) { // tem que checar ne 
        printf("A biblioteca esta vazia.\n");
        return;
    }

    No *atual = lista->inicio; // auxiliar
    printf("Livros na Biblioteca\n");
    while (atual != NULL) {
        printf("Codigo: %d\n", atual->dado.codigo);
        printf("Titulo: %s\n", atual->dado.titulo);
        printf("Autor: %s\n", atual->dado.autor);
        printf("Ano: %d\n", atual->dado.anoPublicacao);
        printf("---------------------------------\n");
        atual = atual->prox;
    }
}

void liberarLista(ListaBiblioteca *lista) {
    No *atual = lista->inicio;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        free(atual); // besteira
        atual = proximo;
    }

    lista->inicio = NULL;
    lista->tamanho = 0;
}