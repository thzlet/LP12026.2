#ifndef TAD_LISTA_ALUNOS_H
#define TAD_LISTA_ALUNOS_H
#include <stdio.h>

// lista heterogenea armazena tipos diferentes de dados;
typedef enum { 
    TIPO_INTEIRO,
    TIPO_REAL,
    TIPO_TEXTO,
    TIPO_ALUNO
} TipoDado; // só uns rotulos 

typedef struct {
    char nome[50]; // texto
    int idade; // int
    float nota; // real
} Aluno;

typedef union {
    int inteiro;
    float real;
    char texto[100];
    Aluno aluno;
} Dado; // só armazena um dado de cada vez, mas pode ser qualquer um dos que estão definidos no enum

typedef struct No {
    TipoDado tipo;  
    Dado dado;     
    struct No *prox;  
} No;

typedef struct {
    No *inicio;
    int tamanho;
} Lista;

// funçoes da lista heterogenea 
Lista* criarLista(void);

int listaVazia(Lista *l);

void inserirInicio(Lista *l, TipoDado tipo, Dado dado);

void inserirFim(Lista *l, TipoDado tipo, Dado dado);

int removerInicio(Lista *l);

void imprimirLista(Lista *l);

void liberarLista(Lista *l);

#endif