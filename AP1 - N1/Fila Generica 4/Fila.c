#include <stdio.h>
#include <stdlib.h>
#include "TAD_FILA_GENERICA.h"

// exemplo pra implementar na fila
typedef struct {
    int id;
    char nome[30];
} Pessoa;

int main(void) {

    Fila *fila = fila_criar();
    if (fila == NULL) {
        fprintf(stderr, "Erro\n");
        return 1;
    }

    // exemplo com inteiros
    int a = 10, b = 20, c = 30;
    fila_enfileirar(fila, &a);
    fila_enfileirar(fila, &b);
    fila_enfileirar(fila, &c);

    printf("Tamanho da fila: %zu\n", fila_tamanho(fila));
    printf("Frente da fila: %d\n", *(int *) fila_frente(fila));

    while (!fila_vazia(fila)) {
        int *valor = (int *) fila_desenfileirar(fila);
        printf("Desenfileirado: %d\n", *valor);
    }

    // exemplo com  alocação 
    Pessoa *p1 = malloc(sizeof(Pessoa));
    p1->id = 1;
    snprintf(p1->nome, sizeof(p1->nome), "Gabriel");

    Pessoa *p2 = malloc(sizeof(Pessoa));
    p2->id = 2;
    snprintf(p2->nome, sizeof(p2->nome), "Iarley");

    fila_enfileirar(fila, p1);
    fila_enfileirar(fila, p2);

    Pessoa *frente = (Pessoa *) fila_frente(fila);
    printf("\nPrimeira pessoa na fila: %d - %s\n", frente->id, frente->nome);

    fila_destruir(fila, free);

    return 0;
}