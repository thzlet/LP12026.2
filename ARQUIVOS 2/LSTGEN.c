#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LSTGEN.h"

#define LSTGEN_LINHA_MAX 4096

static Listagen* lstgen_novo_no(void* elemento) {
    Listagen* no = (Listagen*) malloc(sizeof(Listagen));
    if (no == NULL) {
        fprintf(stderr, "Falha na alocação de memória\n");
        return NULL;
    }
    no->elemento = elemento;
    no->prox = NULL;
    return no;
}

static void lstgen_divide(Listagen* l, Listagen** esq, Listagen** dir) {
    if (l == NULL || l->prox == NULL) {
        *esq = l;
        *dir = NULL;
        return;
    }
    Listagen* lento = l;
    Listagen* rapido = l->prox;
    while (rapido != NULL && rapido->prox != NULL) {
        lento = lento->prox;
        rapido = rapido->prox->prox;
    }
    *esq = l;
    *dir = lento->prox;
    lento->prox = NULL;
}

static Listagen* lstgen_intercala(Listagen* a, Listagen* b, int (*compara)(void*, void*)) {
    Listagen dummy; // espaço reservado pro nó ficticio
    Listagen* cauda = &dummy; // aponta pro ultimo no da lista 
    dummy.prox = NULL;

    while (a != NULL && b != NULL) {
        if (compara(a->elemento, b->elemento) <= 0) {
            cauda->prox = a;
            a = a->prox;
        } else {
            cauda->prox = b;
            b = b->prox;
        }
        cauda = cauda->prox;
    }
    cauda->prox = (a != NULL) ? a : b; 
    return dummy.prox;
}

static Listagen* lstgen_merge_sort(Listagen* l, int (*compara)(void*, void*)) { // ordenação por merge sort ; separa a lista em duas partes menores
    if (l == NULL || l->prox == NULL) {
        return l;
    }
    Listagen* esq;
    Listagen* dir;
    lstgen_divide(l, &esq, &dir);
    esq = lstgen_merge_sort(esq, compara);
    dir = lstgen_merge_sort(dir, compara);
    return lstgen_intercala(esq, dir, compara);
}

Listagen* lstgen_cria() {
    return NULL;
}

int lstgen_vazia(Listagen* l) {
    return (l == NULL);
}

Listagen* lstgen_insere(Listagen* l, void* elemento) {
    Listagen* no = lstgen_novo_no(elemento);
    if (no == NULL) {
        return l; 
    }
    if (l == NULL) {
        return no;
    }
    Listagen* atual = l;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    atual->prox = no;
    return l;
}

void lstgen_percorre(Listagen* l, void (*processa)(void*)) {
    Listagen* atual = l;
    while (atual != NULL) {
        processa(atual->elemento);
        atual = atual->prox;
    }
}

void* lstgen_busca(Listagen* l, int (*compara)(void*, void*), void* dado) {
    Listagen* atual = l;
    while (atual != NULL) {
        if (compara(atual->elemento, dado) == 0) {
            return atual->elemento;
        }
        atual = atual->prox;
    }
    return NULL;
}

Listagen* lstgen_retira(Listagen* l, int (*compara)(void*, void*), void* dado) {
    Listagen* atual = l;
    Listagen* anterior = NULL;

    while (atual != NULL) {
        if (compara(atual->elemento, dado) == 0) {
            if (anterior == NULL) {
                l = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual); 
            return l;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return l; 
}

Listagen* lstgen_duplica(Listagen* l, void* (*duplica)(void*)) {
    Listagen* nova = NULL;
    Listagen* cauda = NULL;
    Listagen* atual = l;

    while (atual != NULL) {
        void* copia = duplica(atual->elemento);
        Listagen* no = lstgen_novo_no(copia);
        if (no == NULL) {
            atual = atual->prox;
            continue;
        }
        if (nova == NULL) {
            nova = no;
            cauda = no;
        } else {
            cauda->prox = no;
            cauda = no;
        }
        atual = atual->prox;
    }
    return nova;
}

void lstgen_libera(Listagen* l) {
    Listagen* atual = l;
    while (atual != NULL) {
        Listagen* proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

Listagen* lstgen_filtra(Listagen* l, int (*criterio)(void*)) {
    Listagen* nova = NULL;
    Listagen* cauda = NULL;
    Listagen* atual = l;

    while (atual != NULL) {
        if (criterio(atual->elemento)) {
            Listagen* no = lstgen_novo_no(atual->elemento);
            if (no != NULL) {
                if (nova == NULL) {
                    nova = no;
                    cauda = no;
                } else {
                    cauda->prox = no;
                    cauda = no;
                }
            }
        }
        atual = atual->prox;
    }
    return nova;
}

Listagen* lstgen_ordena(Listagen* l, int (*compara)(void*, void*)) {
    return lstgen_merge_sort(l, compara);
}

int lstgen_grava_csv(Listagen* l, char* nome_arquivo_csv, char* (*cria_linha_csv)(void*)) {
    FILE* arquivo = fopen(nome_arquivo_csv, "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Nao foi possivel abrir '%s' para escrita\n", nome_arquivo_csv);
        return 0;
    }

    Listagen* atual = l;
    while (atual != NULL) {
        char* linha = cria_linha_csv(atual->elemento);
        if (linha != NULL) {
            fprintf(arquivo, "%s\n", linha);
            free(linha); 
        }
        atual = atual->prox;
    }

    fclose(arquivo);
    return 1;
}

Listagen* lstgen_carrega_csv(char* nome_arquivo_csv, void* (*cria_elemento)(char* linha_csv)) {
    Listagen* l = lstgen_cria();

    FILE* arquivo = fopen(nome_arquivo_csv, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Nao foi possivel abrir '%s' para leitura\n", nome_arquivo_csv);
        return l;
    }

    char linha[LSTGEN_LINHA_MAX];
    while (fgets(linha, LSTGEN_LINHA_MAX, arquivo) != NULL) {
        size_t tam = strlen(linha);
        while (tam > 0 && (linha[tam - 1] == '\n' || linha[tam - 1] == '\r')) {
            linha[tam - 1] = '\0';
            tam--;
        }
        if (tam == 0) {
            continue; 
        }
        void* elemento = cria_elemento(linha);
        if (elemento != NULL) {
            l = lstgen_insere(l, elemento);
        }
    }

    fclose(arquivo);
    return l;
}