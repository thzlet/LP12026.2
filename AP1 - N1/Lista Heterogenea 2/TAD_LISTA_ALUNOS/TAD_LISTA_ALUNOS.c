#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_LISTA_ALUNOS.h"

Lista* criarLista(void) {
    Lista *l = (Lista*) malloc(sizeof(Lista));
    if (l == NULL) {
        printf("Erro\n");
        return NULL;
    }
    l->inicio = NULL;
    l->tamanho = 0;
    return l; // besteira
}

int listaVazia(Lista *l) {
    return (l->inicio == NULL); // besteeeeeira
}

void inserirInicio(Lista *l, TipoDado tipo, Dado dado) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro.\n");
        return;
    }

    novo->tipo = tipo;
    novo->dado = dado;
    novo->prox = l->inicio;
    l->inicio = novo; // mesmo esquema da lista encadeada   

    l->tamanho++; // não pode esquecer 
}

void inserirFim(Lista *l, TipoDado tipo, Dado dado) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro.\n");
        return;
    }

    novo->tipo = tipo;
    novo->dado = dado;
    novo->prox = NULL; // pq vai ser o ultimo no

    if (listaVazia(l)) {
        l->inicio = novo;
    } else {
        No *atual = l->inicio; // auxiliar
        while (atual->prox != NULL) {  
            atual = atual->prox;
        }
        atual->prox = novo; 
    }

    l->tamanho++;
}
 
int removerInicio(Lista *l) {
    if (listaVazia(l)) {
        printf("Lista vazia.\n");
        return 0;
    }

    No *temp = l->inicio; // tranquilo tambem 
    l->inicio = l->inicio->prox;  
    free(temp);

    l->tamanho--;
    return 1;
}

void imprimirLista(Lista *l) {
    if (listaVazia(l)) {
        printf("Lista vazia.\n");
        return;
    }

    No *atual = l->inicio;
    int pos = 1;

    while (atual != NULL) {
        printf("[%d] ", pos);

        switch (atual->tipo) {
            case TIPO_INTEIRO:
                printf("Inteiro: %d\n", atual->dado.inteiro);
                break;
            case TIPO_REAL:
                printf("Real: %.2f\n", atual->dado.real);
                break;
            case TIPO_TEXTO:
                printf("Texto: %s\n", atual->dado.texto);
                break;
            case TIPO_ALUNO:
                printf("Aluno: %s, idade %d, nota %.1f\n",
                       atual->dado.aluno.nome,
                       atual->dado.aluno.idade,
                       atual->dado.aluno.nota);
                break;
            default:
                printf("Tipo desconhecido.\n");
        }

        atual = atual->prox;
        pos++;
    }
}

void liberarLista(Lista *l) {
    No *atual = l->inicio;
    No *proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    free(l);
}