#ifndef OPERACOES_H
#define OPERACOES_H

#include "matriz.h"

typedef enum {
    SAIR = 0,
    ADICAO = 1,
    SUBTRACAO = 2,
    MULTIPLICACAO = 3,
    DIVISAO = 4
} Operacao;

Matriz somarOuSubtrair(const Matriz *a, const Matriz *b, int sinal);
Matriz multiplicar(const Matriz *a, const Matriz *b);
int inverter(const Matriz *m, Matriz *inversa);
int dividir(const Matriz *a, const Matriz *b, Matriz *resultado, int etapa);

/* Aplica a operacao em sequencia: ((M1 op M2) op M3) op ... */
void executarOperacao(const Matriz matrizes[], int quantidade, Operacao op);

#endif
