#include <stdio.h>
#include <math.h>
#include "operacoes.h"
#include "validacao.h"

/* sinal = +1 para adicao, -1 para subtracao */
Matriz somarOuSubtrair(const Matriz *a, const Matriz *b, int sinal) {
    Matriz r = criarMatriz(a->linhas, a->colunas);
    for (int i = 0; i < a->linhas; i++)
        for (int j = 0; j < a->colunas; j++)
            r.dados[i][j] = a->dados[i][j] + sinal * b->dados[i][j];
    return r;
}

Matriz multiplicar(const Matriz *a, const Matriz *b) {
    Matriz r = criarMatriz(a->linhas, b->colunas);
    for (int i = 0; i < a->linhas; i++)
        for (int j = 0; j < b->colunas; j++)
            for (int k = 0; k < a->colunas; k++)
                r.dados[i][j] += a->dados[i][k] * b->dados[k][j];
    return r;
}

/* Gauss-Jordan com pivoteamento parcial. Retorna 0 se for singular. */
int inverter(const Matriz *m, Matriz *inversa) {
    int n = m->linhas;
    Matriz aux = copiarMatriz(m);
    *inversa = criarMatriz(n, n);

    for (int i = 0; i < n; i++)
        inversa->dados[i][i] = 1.0;

    for (int col = 0; col < n; col++) {
        int pivo = col;
        for (int i = col + 1; i < n; i++)
            if (fabs(aux.dados[i][col]) > fabs(aux.dados[pivo][col]))
                pivo = i;

        if (fabs(aux.dados[pivo][col]) < EPSILON) {
            liberarMatriz(&aux);
            liberarMatriz(inversa);
            return 0;
        }

        double *tmp = aux.dados[col];
        aux.dados[col] = aux.dados[pivo];
        aux.dados[pivo] = tmp;
        tmp = inversa->dados[col];
        inversa->dados[col] = inversa->dados[pivo];
        inversa->dados[pivo] = tmp;

        double valorPivo = aux.dados[col][col];
        for (int j = 0; j < n; j++) {
            aux.dados[col][j] /= valorPivo;
            inversa->dados[col][j] /= valorPivo;
        }

        for (int i = 0; i < n; i++) {
            if (i == col) continue;
            double fator = aux.dados[i][col];
            for (int j = 0; j < n; j++) {
                aux.dados[i][j] -= fator * aux.dados[col][j];
                inversa->dados[i][j] -= fator * inversa->dados[col][j];
            }
        }
    }

    liberarMatriz(&aux);
    return 1;
}

/* A / B = A x B^-1. Retorna 0 se a divisao nao puder ser feita. */
int dividir(const Matriz *a, const Matriz *b, Matriz *resultado, int etapa) {
    if (!ehQuadrada(b)) {
        printf("\nErro na etapa %d: a matriz divisora (%dx%d) nao e quadrada.\n",
               etapa, b->linhas, b->colunas);
        return 0;
    }
    if (!podeMultiplicar(a, b)) {
        printf("\nErro na etapa %d: dimensoes incompativeis (%dx%d / %dx%d).\n",
               etapa, a->linhas, a->colunas, b->linhas, b->colunas);
        return 0;
    }

    Matriz inversa;
    if (!inverter(b, &inversa)) {
        printf("\nErro na etapa %d: a matriz divisora e singular "
               "(determinante = 0) e nao possui inversa.\n", etapa);
        return 0;
    }

    *resultado = multiplicar(a, &inversa);
    liberarMatriz(&inversa);
    return 1;
}

/*
 * Calcula uma etapa: resultado acumulado (op) proxima matriz.
 * Retorna 1 em caso de sucesso e 0 se a etapa nao puder ser feita.
 */
static int executarEtapa(const Matriz *a, const Matriz *b, Operacao op,
                         Matriz *novo, int etapa) {
    switch (op) {
        case ADICAO:
        case SUBTRACAO:
            if (!mesmasDimensoes(a, b)) {
                printf("\nErro na etapa %d: %s exige matrizes de mesmas dimensoes "
                       "(%dx%d e %dx%d).\n", etapa,
                       op == ADICAO ? "a adicao" : "a subtracao",
                       a->linhas, a->colunas, b->linhas, b->colunas);
                return 0;
            }
            *novo = somarOuSubtrair(a, b, op == ADICAO ? 1 : -1);
            return 1;

        case MULTIPLICACAO:
            if (!podeMultiplicar(a, b)) {
                printf("\nErro na etapa %d: colunas da primeira (%d) diferente "
                       "das linhas da segunda (%d).\n", etapa, a->colunas, b->linhas);
                return 0;
            }
            *novo = multiplicar(a, b);
            return 1;

        case DIVISAO:
            return dividir(a, b, novo, etapa);

        default:
            return 0;
    }
}

void executarOperacao(const Matriz matrizes[], int quantidade, Operacao op) {
    Matriz resultado = copiarMatriz(&matrizes[0]);

    for (int i = 1; i < quantidade; i++) {
        Matriz novo;
        if (!executarEtapa(&resultado, &matrizes[i], op, &novo, i)) {
            liberarMatriz(&resultado);   /* libera memoria mesmo em caso de erro */
            return;
        }
        liberarMatriz(&resultado);
        resultado = novo;
    }

    exibirMatriz(&resultado, "Matriz resultante");
    liberarMatriz(&resultado);
}
