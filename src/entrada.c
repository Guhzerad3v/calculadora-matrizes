#include <stdio.h>
#include <stdlib.h>
#include "entrada.h"

static void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

static void verificarFimDaEntrada(void) {
    if (feof(stdin)) {
        printf("\nEntrada encerrada.\n");
        exit(EXIT_FAILURE);
    }
}

int lerInteiro(const char *mensagem, int minimo) {
    int valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%d", &valor) == 1 && valor >= minimo) {
            limparBuffer();
            return valor;
        }
        verificarFimDaEntrada();
        printf("Entrada invalida. Informe um inteiro maior ou igual a %d.\n", minimo);
        limparBuffer();
    }
}

double lerReal(const char *mensagem) {
    double valor;
    while (1) {
        printf("%s", mensagem);
        if (scanf("%lf", &valor) == 1) {
            limparBuffer();
            return valor;
        }
        verificarFimDaEntrada();
        printf("Entrada invalida. Informe um numero.\n");
        limparBuffer();
    }
}
