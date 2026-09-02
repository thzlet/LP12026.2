#ifndef TAD_FILA_GENERICA_H
#define TAD_FILA_GENERICA_H
#include <stddef.h>

typedef struct Fila Fila;

Fila *fila_criar(void);

void fila_destruir(Fila *fila, void (*liberar_dado)(void *dado));

int fila_enfileirar(Fila *fila, void *dado);

void *fila_desenfileirar(Fila *fila);

void *fila_frente(Fila *fila);

int fila_vazia(const Fila *fila);

size_t fila_tamanho(const Fila *fila);

#endif 