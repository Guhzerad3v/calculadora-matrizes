#include <stdio.h>
#include <math.h>
#include "operacoes.h"
#include "validacao.h"

#define EPSILON 1e-9

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

/* A / B = A x B^-1 */
int dividir(const Matriz *a, const Matriz *b, Matriz *resultado) {
    if (!ehQuadrada(b) || !podeMultiplicar(a, b)) {
        printf("\nDivisao impossivel: dimensoes incompativeis.\n");
        return 0;
    }

    Matriz inversa;
    if (!inverter(b, &inversa)) {
        printf("\nDivisao impossivel: matriz divisora singular.\n");
        return 0;
    }

    *resultado = multiplicar(a, &inversa);
    liberarMatriz(&inversa);
    return 1;
}

void executarOperacao(const Matriz matrizes[], int quantidade, Operacao op) {
    Matriz resultado = copiarMatriz(&matrizes[0]);

    for (int i = 1; i < quantidade; i++) {
        const Matriz *atual = &matrizes[i];
        Matriz novo;

        if ((op == ADICAO || op == SUBTRACAO) && !mesmasDimensoes(&resultado, atual)) {
            printf("\nOperacao impossivel: dimensoes diferentes.\n");
            liberarMatriz(&resultado);
            return;
        }
        if (op == MULTIPLICACAO && !podeMultiplicar(&resultado, atual)) {
            printf("\nMultiplicacao impossivel: dimensoes incompativeis.\n");
            liberarMatriz(&resultado);
            return;
        }

        if (op == ADICAO)              novo = somarOuSubtrair(&resultado, atual, 1);
        else if (op == SUBTRACAO)      novo = somarOuSubtrair(&resultado, atual, -1);
        else if (op == MULTIPLICACAO)  novo = multiplicar(&resultado, atual);
        else if (!dividir(&resultado, atual, &novo)) {
            liberarMatriz(&resultado);
            return;
        }

        liberarMatriz(&resultado);
        resultado = novo;
    }

    exibirMatriz(&resultado, "Matriz resultante");
    liberarMatriz(&resultado);
}
