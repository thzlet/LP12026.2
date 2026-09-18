#ifndef TAD_ARQUIVO_H
#define TAD_ARQUIVO_H

#include <stdio.h>

// formas geometricas
typedef enum {
    RETANGULO,
    TRIANGULO,
    CIRCULO
} TipoForma;

// formas lidas no arquivo 
typedef struct {
    TipoForma tipo;
    float v1;
    float v2;
} Forma;

Forma *le_formas_arquivo(FILE *fp, int *qtdFormas); // aloca memoria para as formas lidas no arquivo 

float calcula_area(Forma f);

void imprime_forma(Forma f, float area);

#endif 