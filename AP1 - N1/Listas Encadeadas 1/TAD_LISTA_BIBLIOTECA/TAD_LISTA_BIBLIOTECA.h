#ifndef TAD_LISTA_BIBLIOTECA_H
#define TAD_LISTA_BIBLIOTECA_H

// lista encadeadas é uma lista onde os nós ficam ligados por ponteiros
typedef struct Livro {
    int codigo;
    char titulo[100];
    char autor[100];
    int anoPublicacao;
} Livro;
// cada nó armazena o dado e o endereço do  próximo nó;
typedef struct No {
    Livro dado;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
    int tamanho;
} ListaBiblioteca;

// principais funções da lista encadeada;
void criarLista(ListaBiblioteca *lista);

void inserirInicio(ListaBiblioteca *lista, Livro livro);

void inserirFim(ListaBiblioteca *lista, Livro livro);

void removerInicio(ListaBiblioteca *lista);

int listaVazia(ListaBiblioteca *lista);

int tamanhoLista(ListaBiblioteca *lista);

void imprimirLista(ListaBiblioteca *lista);

void liberarLista(ListaBiblioteca *lista);

#endif