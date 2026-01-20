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
               /
             7(R)  ← pai e tio vermelhos
    */

    RB_insert(T, 10);
    RB_insert(T, 5);
    RB_insert(T, 15);
    RB_insert(T, 7);   // pai e tio vermelhos

    if (verificarIntegridade(T))
        printf("Teste Insercao Caso 1: OK\n");
    else
        printf("Teste Insercao Caso 1: FALHA\n");
}

void testeInsercaoCaso2(void) {
    ArvoreRB *T = criarArvoreRB();

    /*
        Estrutura:
            10(B)
           /
         5(R)
            \
             7(R)  ← Caso 2
    */

    RB_insert(T, 10);
    RB_insert(T, 5);
    RB_insert(T, 7);

    if (verificarIntegridade(T))
        printf("Teste Insercao Caso 2: OK\n");
    else
        printf("Teste Insercao Caso 2: FALHA\n");
}

void testeInsercaoCaso3(void) {
    ArvoreRB *T = criarArvoreRB();

    /*
        Estrutura:
            10(B)
           /
         5(R)
        /
      1(R)  ← Caso 3
    */

    RB_insert(T, 10);
    RB_insert(T, 5);
    RB_insert(T, 1);

    if (verificarIntegridade(T))
        printf("Teste Insercao Caso 3: OK\n");
    else
        printf("Teste Insercao Caso 3: FALHA\n");
}

void testeRemocaoNoVermelho(void) {
    ArvoreRB *T = criarArvoreRB();

    RB_insert(T, 10);
    RB_insert(T, 5);
    RB_insert(T, 15);

    // 15 é vermelho
    RB_delete(T, 15);

    if (verificarIntegridade(T))
        printf("Teste Remocao No Vermelho: OK\n");
    else
        printf("Teste Remocao No Vermelho: FALHA\n");
}
