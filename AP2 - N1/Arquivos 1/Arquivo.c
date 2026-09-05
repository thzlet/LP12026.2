#include <stdio.h>

int main (void) {
    int c;
    int nlinhas = 0;
    FILE *fp;

    fp = fopen("entrada.txt", "rt");
    if (fp==NULL) {
        printf("Erro na abertura do arquivo\n");
        return 1;
    }

    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            nlinhas++;
        }
    }
    printf("Número de linhas: %d\n", nlinhas);
    fclose(fp);
    return 0;
}