#include <stdio.h>
#include "../include/arvore_rb.h"

extern int verificarIntegridade(ArvoreRB *T);

void testeInsercaoCaso1(void) {
    ArvoreRB *T = criarArvoreRB();

    /*
        Estrutura gerada:
            10(B)
           /     \
        5(R)    15(R)
           \
            7(R)  ← força Caso 1
    */

    rbInsert(T, 10);
    rbInsert(T, 5);
    rbInsert(T, 15);
    rbInsert(T, 7);   // pai e tio vermelhos

    if (verificarIntegridade(T))
        printf("Teste Insercao Caso 1: OK\n");
    else
        printf("Teste Insercao Caso 1: FALHA\n");
}
