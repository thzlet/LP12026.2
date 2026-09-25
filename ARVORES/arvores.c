#include <stdio.h>
#include "TAD_ARVORE.h"

int main(void) {
    Arvore raiz = criarNo(1);

    Arvore n2 = inserirFilho(raiz, 2);
    Arvore n3 = inserirFilho(raiz, 3);
             inserirFilho(raiz, 7);

             inserirFilho(n2, 4);
             inserirFilho(n2, 5);
             inserirFilho(n3, 6);

    printf("Árvore inicial\n");
    imprimirPreOrdem(raiz, 0);

    printf("\nConsultas\n");
    printf("Total de nós: %d\n", contarNos(raiz));
    printf("Altura: %d\n", altura(raiz));
    printf("Grau: %d\n", grauArvore(raiz));

    Arvore encontrado = buscarNo(raiz, 5);
    if (encontrado != NULL)
        printf("No encontrado! E folha? %s\n", isFolha(encontrado) ? "sim" : "nao");
    else
        printf("No nao encontrado.\n");

    printf("Nivel do no 6: %d\n", nivelDoNo(raiz, 6, 0));
    printf("Nivel do no 1 (raiz): %d\n", nivelDoNo(raiz, 1, 0));

    listarFilhos(raiz);
    listarFilhos(n2);

    printf("\nRemovendo subarvore do no 3 (e seu filho 6)\n");
    removerSubarvore(&raiz, 3);
    imprimirPreOrdem(raiz, 0);
    printf("Total de nos apos remocao: %d\n", contarNos(raiz));

    printf("\nLiberando a arvore\n");
    liberarArvore(&raiz);
    printf("raiz == NULL apos liberar? %s\n", (raiz == NULL) ? "sim" : "nao");

    return 0;
}