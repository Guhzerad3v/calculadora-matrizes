# Calculadora de Matrizes em C

## Objetivo

Sistema de terminal que cadastra duas ou mais matrizes e faz operações matemáticas entre elas, validando as regras de cada operação.

## Funcionalidades

- Cadastro de 2 ou mais matrizes (linhas, colunas e cada elemento)
- Operações: **adição, subtração, multiplicação e divisão** (`A / B = A × B⁻¹`)
- Operações feitas em sequência, da esquerda para a direita: `((M1 op M2) op M3) ...`
- Avisos quando a operação é impossível: dimensões incompatíveis, divisora não quadrada ou singular
- Validação de entradas inválidas (letras, valores fora do limite)
- Menu que se repete até o usuário escolher sair

## Como compilar e executar

```bash
gcc -Wall -std=c99 src/*.c -o matrizes -lm
./matrizes
```

No Windows: `matrizes.exe` no lugar de `./matrizes`.

## Estrutura e funções

| Arquivo | Responsabilidade | Funções |
|---|---|---|
| `main.c` | Fluxo principal e menu | `main`, `exibirMenu`, `exibirCadastradas` |
| `entrada.c` | Leitura validada | `lerInteiro`, `lerReal` |
| `matriz.c` | Memória, leitura e exibição | `criarMatriz`, `liberarMatriz`, `copiarMatriz`, `lerMatriz`, `exibirMatriz` |
| `validacao.c` | Regras de dimensão | `mesmasDimensoes`, `podeMultiplicar`, `ehQuadrada` |
| `operacoes.c` | Cálculos | `somarOuSubtrair`, `multiplicar`, `inverter`, `dividir`, `executarOperacao` |

A inversa é calculada por **Gauss-Jordan**. Se um pivô for zero, a matriz é singular e o programa avisa.

## Exemplos de uso

Divisão `[1 2; 3 4] / [2 0; 1 2]`:
```
Escolha uma opcao: 4

Matriz resultante (2x2):
|       0.00       1.00 |
|       0.50       2.00 |
```

Divisora singular `[1 2; 2 4]`:
```
Erro na etapa 1: a matriz divisora e singular (determinante = 0) e nao possui inversa.
```

## Testes realizados

| Cenário | Resultado |
|---|---|
| Adição `[1 2; 3 4] + [2 0; 1 2]` | `[3 2; 4 6]` ✅ |
| Multiplicação de 3 matrizes `[5 6] × [1; 1] × [7 8 9]` | `[77 88 99]` ✅ |
| Divisão `[1 2; 3 4] / [2 0; 1 2]` | `[0 1; 0,5 2]` ✅ |
| Divisora singular | Aviso de singular ✅ |
| Subtração 1x2 − 2x1 | Aviso de dimensões ✅ |
| Quantidade `1` ou `abc` | Pede de novo ✅ |
