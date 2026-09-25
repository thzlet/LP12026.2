#include <stdio.h>
#include <stdlib.h>
#include "TAD_ARVORE.h"

static int removerAux(Arvore no, int valor);

Arvore criarNo(int valor) {
    Arvore novo = (Arvore) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro\n");
        exit(1);
    }
    novo->valor = valor;
    novo->filho = NULL;
    novo->irmao = NULL;
    return novo;
}

Arvore inserirFilho(Arvore pai, int valor) {
    if (pai == NULL) return NULL;

    Arvore novo = criarNo(valor);

    if (pai->filho == NULL) {
        pai->filho = novo;
    } else {
        Arvore atual = pai->filho;
        while (atual->irmao != NULL) {
            atual = atual->irmao;
        }
        atual->irmao = novo;
    }
    return novo;
}

Arvore buscarNo(Arvore no, int valor) {
    if (no == NULL) return NULL;
    if (no->valor == valor) return no;

    Arvore filho = no->filho;
    while (filho != NULL) {
        Arvore achou = buscarNo(filho, valor);
        if (achou != NULL) return achou;
        filho = filho->irmao;
    }
    return NULL;
}

int contarNos(Arvore no) {
    if (no == NULL) return 0;

    int total = 1;
    Arvore filho = no->filho;
    while (filho != NULL) {
        total += contarNos(filho);
        filho = filho->irmao;
    }
    return total;
}

// para cada nó, calcula a altura de cada filho e fica com a maior
int altura(Arvore no) {
    if (no == NULL) return -1;

    int maior = -1;
    Arvore filho = no->filho;
    while (filho != NULL) {
        int h = altura(filho);
        if (h > maior) maior = h;
        filho = filho->irmao;
    }
    return maior + 1;
}

// grau é o maior número de filhos que qualquer nó da árvore possui; percorre tudo comparando;
int grauArvore(Arvore no) {
    if (no == NULL) return 0;

    int grauDesteNo = 0;
    Arvore filho = no->filho;
    while (filho != NULL) {
        grauDesteNo++;
        filho = filho->irmao;
    }

    int maior = grauDesteNo;
    filho = no->filho;
    while (filho != NULL) {
        int g = grauArvore(filho);
        if (g > maior) maior = g;
        filho = filho->irmao;
    }
    return maior;
}

int isFolha(Arvore no) {
    return (no != NULL && no->filho == NULL);
}

// desce contando os niveis ate achar o valor 
int nivelDoNo(Arvore no, int valor, int nivelAtual) {
    if (no == NULL) return -1;
    if (no->valor == valor) return nivelAtual;

    Arvore filho = no->filho;
    while (filho != NULL) {
        int nivel = nivelDoNo(filho, valor, nivelAtual + 1);
        if (nivel != -1) return nivel;
        filho = filho->irmao;
    }
    return -1;
}

// visita o nó, imprime com indentação proporcional a profundidade, depois desce em cada filho
void imprimirPreOrdem(Arvore no, int profundidade) {
    if (no == NULL) return;

    for (int i = 0; i < profundidade; i++) {
        printf("  ");
    }
    printf("- %d\n", no->valor);

    Arvore filho = no->filho;
    while (filho != NULL) {
        imprimirPreOrdem(filho, profundidade + 1);
        filho = filho->irmao;
    }
}

void listarFilhos(Arvore no) {
    if (no == NULL) return;

    printf("Filhos de %d: ", no->valor);
    Arvore filho = no->filho;
    if (filho == NULL) {
        printf("(nenhum)\n");
        return;
    }
    while (filho != NULL) {
        printf("%d ", filho->valor);
        filho = filho->irmao;
    }
    printf("\n");
}
// precisa achar o pai do nó a remover p religar filho/irmao 
int removerSubarvore(Arvore *raiz, int valor) {
    if (*raiz == NULL) return 0;

    if ((*raiz)->valor == valor) {
        liberarArvore(raiz);
        return 1;
    }
    return removerAux(*raiz, valor);
}

static int removerAux(Arvore no, int valor) {
    Arvore anterior = NULL;
    Arvore atual = no->filho;

    while (atual != NULL) {
        if (atual->valor == valor) {
            if (anterior == NULL) {
                no->filho = atual->irmao;   
            } else {
                anterior->irmao = atual->irmao; 
            }
            atual->irmao = NULL;
            liberarArvore(&atual);
            return 1;
        }
        anterior = atual;
        atual = atual->irmao;
    }

    atual = no->filho;
    while (atual != NULL) {
        if (removerAux(atual, valor)) return 1;
        atual = atual->irmao;
    }

    return 0;
}

void liberarArvore(Arvore *raiz) {
    if (*raiz == NULL) return;

    Arvore filho = (*raiz)->filho;
    while (filho != NULL) {
        Arvore proximo = filho->irmao;
        liberarArvore(&filho);
        filho = proximo;
    }

    free(*raiz);
    *raiz = NULL;
}