#include <stdio.h>
#include "TAD_LISTA_BIBLIOTECA.h"

int main() {
    ListaBiblioteca biblioteca;
    criarLista(&biblioteca);

    Livro l1 = {1, "O Senhor dos Aneis", "J.R.R. Tolkien", 1954};
    Livro l2 = {2, "1984", "George Orwell", 1949};
    Livro l3 = {3, "Dom Casmurro", "Machado de Assis", 1899};

    inserirFim(&biblioteca, l1);
    inserirFim(&biblioteca, l2);
    inserirInicio(&biblioteca, l3);

    imprimirLista(&biblioteca);

    printf("\nQuantidade de livros: %d\n\n", tamanhoLista(&biblioteca));

    removerInicio(&biblioteca);

    printf("Apos remover o primeiro livro:\n");
    imprimirLista(&biblioteca);

    liberarLista(&biblioteca);

    return 0;
}