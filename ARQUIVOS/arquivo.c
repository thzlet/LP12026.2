#include <stdio.h>
#include <stdlib.h>
#include "TAD_ARQUIVO.h"

int main(int argc, char *argv[]) {
    const char *nomeArquivo = (argc > 1) ? argv[1] : "formas.txt";

    FILE *fp = fopen(nomeArquivo, "r");
    if (fp == NULL) {
        fprintf(stderr, "Não é possível abrir o arquivo '%s'.\n", nomeArquivo);
        return 1;
    }

    int qtdFormas = 0;
    Forma *formas = le_formas_arquivo(fp, &qtdFormas);
    fclose(fp);

    if (formas == NULL || qtdFormas == 0) {
        printf("Nenhuma forma em '%s'.\n", nomeArquivo);
        free(formas);
        return 0;
    }

    printf("Formas em '%s':\n\n", nomeArquivo);

    float areaTotal = 0.0f;
    for (int i = 0; i < qtdFormas; i++) {
        float area = calcula_area(formas[i]);
        imprime_forma(formas[i], area);
        areaTotal += area;
    }

    printf("\nTotal de formas: %d\n", qtdFormas);
    printf("Area total: %.2f\n", areaTotal);

    free(formas);
    return 0;
}