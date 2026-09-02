#include <stdio.h>
#include <string.h>
#include "TAD_LISTA_ALUNOS.h"

int main(void) {

    Lista *minhaLista = criarLista();

    if (minhaLista == NULL) {
        return 1;
    }

    Dado d1;
    d1.inteiro = 10;
    inserirFim(minhaLista, TIPO_INTEIRO, d1);

    Dado d2;
    d2.real = 3.14f;
    inserirFim(minhaLista, TIPO_REAL, d2);

    Dado d3;
    strcpy(d3.texto, "hellous");
    inserirFim(minhaLista, TIPO_TEXTO, d3);

    Dado d4;
    strcpy(d4.aluno.nome, "Let");
    d4.aluno.idade = 20;
    d4.aluno.nota = 9.5f;
    inserirFim(minhaLista, TIPO_ALUNO, d4);

    Dado d5;
    strcpy(d5.aluno.nome, "Gabriel");
    d5.aluno.idade = 22;
    d5.aluno.nota = 8.0f;
    inserirInicio(minhaLista, TIPO_ALUNO, d5);

    printf("Lista\n");
    imprimirLista(minhaLista);
    printf("Tamanho: %d\n\n", minhaLista->tamanho);

    removerInicio(minhaLista);

    printf("\nLista apos remover o inicio\n");
    imprimirLista(minhaLista);
    printf("Tamanho da lista: %d\n\n", minhaLista->tamanho);

    liberarLista(minhaLista);

    return 0;
}