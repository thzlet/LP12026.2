#include <stdio.h>
#include <stdlib.h>
#include "TAD_ARQUIVO.h"

#define TAM_LINHA 121
#define CAPACIDADE_INICIAL 8

Forma *le_formas_arquivo(FILE *fp, int *qtdFormas) {
    char c;
    float v1, v2;
    char linha[TAM_LINHA];

    int capacidade = CAPACIDADE_INICIAL;
    int qtd = 0;
    Forma *formas = (Forma *) malloc(capacidade * sizeof(Forma));
    if (formas == NULL) {
        fprintf(stderr, "Erro na alocação de memória\n"); // stderr envia mensagem de erro padrão 
        *qtdFormas = 0;
        return NULL;
    }

    while (fgets(linha, TAM_LINHA, fp)) {
        int n = sscanf(linha, " %c %f %f", &c, &v1, &v2);

        if (n > 0) {
            switch (c) {

                case '#':
                    /* desprezar linha de comentário */
                    break;

                case 'r':
                    if (n != 3) {
                        fprintf(stderr, "Formato invalido p retangulo: %s", linha);
                    } else {
                        // retangulo 
                        if (qtd == capacidade) {
                            capacidade *= 2;
                            formas = (Forma *) realloc(formas, capacidade * sizeof(Forma));
                        }
                        formas[qtd].tipo = RETANGULO;
                        formas[qtd].v1 = v1;
                        formas[qtd].v2 = v2;
                        qtd++;
                    }
                    break;

                case 't':
                    if (n != 3) {
                        fprintf(stderr, "Formato invalido p triangulo: %s", linha);
                    } else {
                        // triangulo 
                        if (qtd == capacidade) {
                            capacidade *= 2;
                            formas = (Forma *) realloc(formas, capacidade * sizeof(Forma));
                        }
                        formas[qtd].tipo = TRIANGULO;
                        formas[qtd].v1 = v1;
                        formas[qtd].v2 = v2;
                        qtd++;
                    }
                    break;

                case 'c':
                    if (n != 2) {
                        fprintf(stderr, "Formato invalido p circulo: %s", linha);
                    } else {
                        // circulo 
                        if (qtd == capacidade) {
                            capacidade *= 2;
                            formas = (Forma *) realloc(formas, capacidade * sizeof(Forma));
                        }
                        formas[qtd].tipo = CIRCULO;
                        formas[qtd].v1 = v1;
                        formas[qtd].v2 = 0.0f;
                        qtd++;
                    }
                    break;

                default:
                    fprintf(stderr, "Codigo não aceito: %s", linha);
                    break;
            }
        }
    }

    *qtdFormas = qtd;
    return formas;
}

float calcula_area(Forma f) { // calculo das áreas 
    switch (f.tipo) {
        case RETANGULO:
            return f.v1 * f.v2;
        case TRIANGULO:
            return (f.v1 * f.v2) / 2.0f;
        case CIRCULO:
            return 3.14159265f * f.v1 * f.v1;
        default:
            return 0.0f;
    }
}

// imprimindo 
void imprime_forma(Forma f, float area) {
    switch (f.tipo) {
        case RETANGULO:
            printf("Retangulo  - base: %.2f, altura: %.2f, area: %.2f\n",
                   f.v1, f.v2, area);
            break;
        case TRIANGULO:
            printf("Triangulo - base: %.2f, altura: %.2f, area: %.2f\n",
                   f.v1, f.v2, area);
            break;
        case CIRCULO:
            printf("Circulo - raio: %.2f, area: %.2f\n",
                   f.v1, area);
            break;
    }
}