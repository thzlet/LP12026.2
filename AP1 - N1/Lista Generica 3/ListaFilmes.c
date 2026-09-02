#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TAD_LISTA_FILMES.h"

typedef struct {
    char titulo[100];
    char genero[50];
    int ano;
} Filme;

void imprimirFilme(void *dado)
{
    Filme *filme = (Filme*) dado;

    printf("Titulo: %s\n", filme->titulo);
    printf("Genero: %s\n", filme->genero);
    printf("Ano: %d\n", filme->ano);
    printf("-------------------------\n");
}

void liberarFilme(void *dado)
{
    free(dado);
}

Filme* criarFilme(char titulo[], char genero[], int ano)
{
    Filme *filme = (Filme*) malloc(sizeof(Filme));

    if (filme == NULL)
        return NULL;

    strcpy(filme->titulo, titulo);
    strcpy(filme->genero, genero);
    filme->ano = ano;

    return filme;
}

int main(void)
{
    Lista *lista;

    Filme *filme1;
    Filme *filme2;
    Filme *filme3;

    Filme *removido;

    lista = criarLista();

    if (lista == NULL)
        return 1;

    filme1 = criarFilme("Interestelar", "Ficcao Cientifica", 2014);
    filme2 = criarFilme("O Senhor dos Aneis", "Fantasia", 2001);
    filme3 = criarFilme("Toy Story", "Animacao", 1995);

    inserirFim(lista, filme1);
    inserirFim(lista, filme2);
    inserirInicio(lista, filme3);

    printf("FILMES DA LISTA\n");
    printf("=========================\n");

    imprimirLista(lista, imprimirFilme);

    printf("\nTamanho da lista: %d\n", lista->tamanho);

    printf("\nRemovendo o primeiro filme...\n");

    removido = (Filme*) removerInicio(lista);

    if (removido != NULL) {
        printf("Filme removido: %s\n", removido->titulo);
        free(removido);
    }

    printf("\nFILMES APOS REMOCAO\n");
    printf("=========================\n");

    imprimirLista(lista, imprimirFilme);

    printf("\nTamanho da lista: %d\n", lista->tamanho);

    liberarLista(lista, liberarFilme);

    return 0;
}

// falta testar algumas