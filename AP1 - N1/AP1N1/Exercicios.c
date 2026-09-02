/*
questão 1 - apenas as funções de manipulação de pilhas 
retorna a pagina anterior do historico (pilha undo) armazenando
a pagina atual na pilha redo. retorna a nova pagina a ser exibida. 
caso nao haja pagina anterior, retorna NULL.

char* voltar_pagina(Pilha* undo, Pilha* redo) {
    if (pilha_vazia(undo)) {
        return NULL;
    }

    // removendo a pág atual de undo e guardando em redo
    char* pagina_atual = pilha_desempilhar(undo);
    pilha_empilhar(redo, pagina_atual);

    if (pilha_vazia(undo)) {
        return NULL;
    }

    return pilha_topo(undo);
}
*/
