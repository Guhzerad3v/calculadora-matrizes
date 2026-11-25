#include <stdio.h>
#include <stdlib.h>
#include "entrada.h"
#include "matriz.h"

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

    for (int i = 0; i < quantidade; i++) {
        char titulo[32];
        snprintf(titulo, sizeof(titulo), "Matriz %d", i + 1);
        exibirMatriz(&matrizes[i], titulo);
    }

    for (int i = 0; i < quantidade; i++)
        liberarMatriz(&matrizes[i]);
    free(matrizes);

    return EXIT_SUCCESS;
}
