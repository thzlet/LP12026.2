#ifndef TAD_ARVORE_H
#define TAD_ARVORE_H

// em uma arvore generica, um nó pode ter n filhos
typedef struct no {
    int valor;
    struct no *filho;  // ponteiro  pro primeiro filho 
    struct no *irmao;  // ponteiro pro próximo "irmão"
} No;

// os filhos de um nó viram uma lista ligada, onde cada nó aponta para o próximo irmão
// o último aponta para NULL
typedef No* Arvore;

Arvore criarNo(int valor); // cria um nó vazio com o valor dado 
Arvore inserirFilho(Arvore pai, int valor); // add um filho ao nó pai e retorna o novo filho 

Arvore buscarNo(Arvore raiz, int valor); // procura um nó com determinado valor 
int    contarNos(Arvore raiz);
int    altura(Arvore raiz);
int    grauArvore(Arvore raiz);
int    isFolha(Arvore no); 
int    nivelDoNo(Arvore raiz, int valor, int nivelAtual);

void imprimirPreOrdem(Arvore raiz, int profundidade);
void listarFilhos(Arvore no); // filhos diretos de determinado nó 

int  removerSubarvore(Arvore *raiz, int valor);
void liberarArvore(Arvore *raiz);

#endif