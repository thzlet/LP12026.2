#ifndef LSTGEN_H
#define LSTGEN_H

typedef struct no_lstgen {
    void* elemento;
    struct no_lstgen* prox;
} Listagen;

Listagen* lstgen_cria();

int lstgen_vazia(Listagen* l);

Listagen* lstgen_insere(Listagen* l, void* elemento);

void lstgen_percorre(Listagen* l, void (*processa)(void*));

void* lstgen_busca(Listagen* l, int (*compara)(void*, void*), void* dado);

Listagen* lstgen_retira(Listagen* l, int (*compara)(void*, void*), void* dado);

Listagen* lstgen_duplica(Listagen* l, void* (*duplica)(void*));

void lstgen_libera(Listagen* l);

Listagen* lstgen_filtra(Listagen* l, int (*criterio)(void*));

Listagen* lstgen_ordena(Listagen* l, int (*compara)(void*, void*));

int lstgen_grava_csv(Listagen* l, char* nome_arquivo_csv, char* (*cria_linha_csv)(void*));

Listagen* lstgen_carrega_csv(char* nome_arquivo_csv, void* (*cria_elemento)(char* linha_csv));

#endif