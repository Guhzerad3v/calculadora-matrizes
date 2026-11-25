#include <stdio.h>
#include <stdlib.h>
#include "entrada.h"
#include "matriz.h"
#include "operacoes.h"

static Operacao exibirMenu(void) {
    printf("\n========== MENU ==========\n");
    printf("1 - Adicao\n");
    printf("2 - Subtracao\n");
    printf("3 - Multiplicacao\n");
    printf("4 - Divisao matricial (A x B^-1)\n");
    printf("0 - Sair\n");

    int opcao;
    do {
        opcao = lerInteiro("Escolha uma opcao: ", 0);
        if (opcao > DIVISAO)
            printf("Opcao invalida.\n");
    } while (opcao > DIVISAO);

    return (Operacao) opcao;
}

int main(void) {
    printf("===== CALCULADORA DE MATRIZES =====\n");

    int quantidade = lerInteiro("Quantas matrizes deseja utilizar (minimo 2)? ", 2);

    Matriz *matrizes = malloc(quantidade * sizeof(Matriz));
    if (matrizes == NULL) {
        fprintf(stderr, "Erro: memoria insuficiente.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < quantidade; i++)
        matrizes[i] = lerMatriz(i);

    Operacao op;
    while ((op = exibirMenu()) != SAIR)
        executarOperacao(matrizes, quantidade, op);

    for (int i = 0; i < quantidade; i++)
        liberarMatriz(&matrizes[i]);
    free(matrizes);

    printf("Programa encerrado.\n");
    return EXIT_SUCCESS;
}
