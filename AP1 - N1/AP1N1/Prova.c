/* QUESTÃO 1 a: chama a próxima senha urgente pra atendimento ; acertei

void chama_proxima_urgencia (Pilha* urgencias) {
    if (pilha_vazia(urgencias)) { // vendo se tem alguma urgencia
        printf("Nenhuma urgencia pendente\n");
        return;
    }

    Senha* s = (Senha*) pilha_desempilhar(urgencias);
    printf("Chamando senha urgente: %d - %s\n", s->numero, s->nome);
    free(s); // liberei a memoria da senha 
}

QUESTÃO 1 b: registra uma senha nova no final da lista de espera ; acertei

void registra_senha_normal(Fila* normais, int* proximo_numero, char* nome) {
    Senha* s = (Senha*) malloc(sizeof(Senha)); // aloquei memória pra senha

    s->numero = *proximo_numero; // num da senha eh o valor apontado por proximo numero
    strcpy(s->nome, nome); // ia usar um string.h, usei pq é char
    s->urgente = 0;

    (*proximo_numero)++;

    fila_insere(normais, s); // foi pro final da fila 
}

QUESTÃO 2 a: callback de comparação com lstgen_busca e lstgen_retira ; acertei

int mesmo_codigo(void* info, void* dado) {
    Livro* livro = (Livro*) info; // info aponta pro livro  
    int* codigo_procurado = (int*) dado; // dado aponta pro codigo que to procurando 

    return livro->codigo == *codigo_procurado; // comparando com os codigos da lista
}

QUESTÃO 2 b: empresta o livro do código ; acertei 

int empresta_livro(Listagen* biblioteca, int codigo) {
    Livro* livro = (Livro*) lstgen_busca(biblioteca, mesmo_codigo, &codigo);

    if (livro == NULL) {
        return 0;
    }

    if (livro->emprestado == 1) {
        return 0;
    }

    livro->emprestado = 1;
    return 1;
}
*/
