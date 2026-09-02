#ifndef TAD_PILHA_GENERICA_H
#define TAD_PILHA_GENERICA_H

#include <stddef.h>

typedef struct Pilha Pilha;

Pilha *pilha_criar(void);

void pilha_destruir(Pilha *pilha, void (*liberar_dado)(void *dado));

int pilha_empilhar(Pilha *pilha, void *dado);

void *pilha_desempilhar(Pilha *pilha);

void *pilha_topo(Pilha *pilha);

int pilha_vazia(const Pilha *pilha);

size_t pilha_tamanho(const Pilha *pilha);

#endif 