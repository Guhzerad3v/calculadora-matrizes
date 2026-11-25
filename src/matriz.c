#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "entrada.h"

static void erroMemoria(void) {
    fprintf(stderr, "Erro: memoria insuficiente.\n");
    exit(EXIT_FAILURE);
}

Matriz criarMatriz(int linhas, int colunas) {
    Matriz m;
    m.linhas = linhas;
    m.colunas = colunas;
    m.dados = malloc(linhas * sizeof(double *));
    if (m.dados == NULL) erroMemoria();

    for (int i = 0; i < linhas; i++) {
        m.dados[i] = calloc(colunas, sizeof(double));
        if (m.dados[i] == NULL) erroMemoria();
    }
    return m;
}

void liberarMatriz(Matriz *m) {
    if (m->dados == NULL) return;
    for (int i = 0; i < m->linhas; i++)
        free(m->dados[i]);
    free(m->dados);
    m->dados = NULL;
}

Matriz copiarMatriz(const Matriz *origem) {
    Matriz copia = criarMatriz(origem->linhas, origem->colunas);
    for (int i = 0; i < origem->linhas; i++)
        for (int j = 0; j < origem->colunas; j++)
            copia.dados[i][j] = origem->dados[i][j];
    return copia;
}

Matriz lerMatriz(int indice) {
    char mensagem[64];

    printf("\n--- Matriz %d ---\n", indice + 1);
    int linhas = lerInteiro("Quantidade de linhas: ", 1);
    int colunas = lerInteiro("Quantidade de colunas: ", 1);

    Matriz m = criarMatriz(linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            snprintf(mensagem, sizeof(mensagem), "Elemento [%d][%d]: ", i + 1, j + 1);
            m.dados[i][j] = lerReal(mensagem);
        }
    }
    return m;
}

void exibirMatriz(const Matriz *m, const char *titulo) {
    printf("\n%s (%dx%d):\n", titulo, m->linhas, m->colunas);
    for (int i = 0; i < m->linhas; i++) {
        printf("| ");
        for (int j = 0; j < m->colunas; j++)
            printf("%10.2f ", m->dados[i][j]);
        printf("|\n");
    }
}
