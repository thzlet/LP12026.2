#ifndef TAD_LISTA_FILMES.h
#define TAD_LISTA_FILMES.h

// aqui dificultou 
// lista genericas possuem diferentes tipos de dados sem precisar de listas especificas para cada tipo de dado;

typedef struct {
    void *dado;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
    int tamanho;
} Lista;

// funções principais da generica 
Lista* criarLista(void);

int listaVazia(Lista* lista);

int inserirInicio(Lista* lista, void *dado);

int inserirFim(Lista* l, void  *dado);

void* removerInicio(Lista* lista);

void* removerFim(Lista* lista);

void imprimirLista(Lista* lista, void (*imprimir)(void*));

void liberarLista(Lista* lista, void (*liberar)(void*));

void percorrerLista(Lista *lista, void (*processa)(void *));

void* buscarLista(Lista *lista, int (*compara)(void *, void *), void *dado);

void* retirarLista(Lista *lista, int (*compara)(void *, void *), void *dado);

Lista* duplicarLista(Lista *lista, void* (*duplica)(void *));

Lista* filtrarLista(Lista *lista, int (*criterio)(void *));

Lista* ordenarLista(Lista *lista, int (*compara)(void *, void *));

#endif