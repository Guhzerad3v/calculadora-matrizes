#ifndef MATRIZ_H
#define MATRIZ_H

#define EPSILON 1e-9   /* tolerancia para considerar um valor como zero */

typedef struct {
    int linhas;
    int colunas;
    double **dados;
} Matriz;

Matriz criarMatriz(int linhas, int colunas);
void liberarMatriz(Matriz *m);
Matriz copiarMatriz(const Matriz *origem);

Matriz lerMatriz(int indice);
void exibirMatriz(const Matriz *m, const char *titulo);

#endif
