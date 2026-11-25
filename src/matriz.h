#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct {
    int linhas;
    int colunas;
    double **dados;
} Matriz;

Matriz criarMatriz(int linhas, int colunas);
void liberarMatriz(Matriz *m);

Matriz lerMatriz(int indice);
void exibirMatriz(const Matriz *m, const char *titulo);

#endif
