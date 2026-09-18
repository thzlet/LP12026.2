#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LSTGEN.h"

#define LINHA_CSV_MAX 128

typedef struct {
    char nome[50];
    int idade;
} Pessoa;

static Pessoa* pessoa_cria(const char* nome, int idade) {
    Pessoa* p = (Pessoa*) malloc(sizeof(Pessoa));
    strncpy(p->nome, nome, sizeof(p->nome) - 1);
    p->nome[sizeof(p->nome) - 1] = '\0';
    p->idade = idade;
    return p;
}

void pessoa_imprime(void* elemento) {
    Pessoa* p = (Pessoa*) elemento;
    printf("  - %s (%d anos)\n", p->nome, p->idade);
}

int pessoa_compara_nome(void* elemento, void* dado) {
    Pessoa* p = (Pessoa*) elemento;
    char* nome = (char*) dado;
    return strcmp(p->nome, nome);
}

int pessoa_compara_idade_asc(void* e1, void* e2) {
    Pessoa* p1 = (Pessoa*) e1;
    Pessoa* p2 = (Pessoa*) e2;
    return p1->idade - p2->idade;
}

void* pessoa_duplica(void* elemento) {
    Pessoa* p = (Pessoa*) elemento;
    return pessoa_cria(p->nome, p->idade);
}

int pessoa_e_maior_idade(void* elemento) {
    Pessoa* p = (Pessoa*) elemento;
    return p->idade >= 18;
}

char* pessoa_cria_linha_csv(void* elemento) {
    Pessoa* p = (Pessoa*) elemento;
    char* linha = (char*) malloc(80 * sizeof(char));
    snprintf(linha, 80, "%s,%d", p->nome, p->idade);
    return linha;
}

void* pessoa_cria_elemento_csv(char* linha_csv) {
    char nome[50];
    int idade;
    char copia[LINHA_CSV_MAX];
    strncpy(copia, linha_csv, sizeof(copia) - 1);
    copia[sizeof(copia) - 1] = '\0';

    char* token = strtok(copia, ",");
    if (token == NULL) { return NULL; }
    strncpy(nome, token, sizeof(nome) - 1);
    nome[sizeof(nome) - 1] = '\0';

    token = strtok(NULL, ",");
    idade = (token != NULL) ? atoi(token) : 0;

    return pessoa_cria(nome, idade);
}

void libera_lista_de_pessoas(Listagen* l) {
    Listagen* atual = l;
    while (atual != NULL) {
        free(atual->elemento);
        atual = atual->prox;
    }
    lstgen_libera(l);
}

int main() {
    printf("Criando e inserindo\n");
    Listagen* pessoas = lstgen_cria();
    printf("Lista vazia? %s\n", lstgen_vazia(pessoas) ? "sim" : "nao");

    pessoas = lstgen_insere(pessoas, pessoa_cria("Gabriel", 21));
    pessoas = lstgen_insere(pessoas, pessoa_cria("Karol", 22));
    pessoas = lstgen_insere(pessoas, pessoa_cria("Iarley", 21));
    pessoas = lstgen_insere(pessoas, pessoa_cria("Letícia", 21));
    pessoas = lstgen_insere(pessoas, pessoa_cria("Santiago", 24));

    printf("Lista vazia? %s\n", lstgen_vazia(pessoas) ? "sim" : "nao");
    printf("Conteudo:\n");
    lstgen_percorre(pessoas, pessoa_imprime);

    printf("\nBuscando\n");
    Pessoa* encontrada = (Pessoa*) lstgen_busca(pessoas, pessoa_compara_nome, "Carla");
    if (encontrada != NULL) {
        printf("Encontrada: %s, %d anos\n", encontrada->nome, encontrada->idade);
    } else {
        printf("Nao encontrada\n");
    }

    printf("\nRetirando\n");
    pessoas = lstgen_retira(pessoas, pessoa_compara_nome, "Letícia");
    printf("Lista apos remover 'Letícia':\n");
    lstgen_percorre(pessoas, pessoa_imprime);

    printf("\nDuplicando\n");
    Listagen* copia = lstgen_duplica(pessoas, pessoa_duplica);
    printf("Copia da lista:\n");
    lstgen_percorre(copia, pessoa_imprime);

    printf("\nFiltrando\n");
    Listagen* maiores = lstgen_filtra(pessoas, pessoa_e_maior_idade);
    printf("Maiores de 18 anos:\n");
    lstgen_percorre(maiores, pessoa_imprime);

    printf("\nOrdenando por idade\n");
    pessoas = lstgen_ordena(pessoas, pessoa_compara_idade_asc);
    printf("Lista ordenada por idade:\n");
    lstgen_percorre(pessoas, pessoa_imprime);

    printf("\nGravando CSV\n");
    int ok = lstgen_grava_csv(pessoas, "pessoas.csv", pessoa_cria_linha_csv);
    printf("Gravacao %s\n", ok ? "bem-sucedida" : "falhou");

    printf("\nCarregando CSV\n");
    Listagen* carregadas = lstgen_carrega_csv("pessoas.csv", pessoa_cria_elemento_csv);
    printf("Lista carregada do arquivo pessoas.csv:\n");
    lstgen_percorre(carregadas, pessoa_imprime);

    printf("\nLiberando memória\n");

    lstgen_libera(maiores);

    libera_lista_de_pessoas(pessoas);
    libera_lista_de_pessoas(copia);
    libera_lista_de_pessoas(carregadas);

    printf("Memoria liberada\n");
    return 0;
}