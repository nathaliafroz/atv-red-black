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


void testeRemocaoCaso1(void) {
    ArvoreRB *T = criarArvoreRB();

    /*
        Estrutura antes da remoção:
                10(B)
               /     \
            5(B)     20(R)
                     /
                  15(B)

        Remoção de 5 força Caso 1 (irmão vermelho)
    */

    RB_insert(T, 10);
    RB_insert(T, 5);
    RB_insert(T, 20);
    RB_insert(T, 15);

    RB_delete(T, 5);

    if (verificarIntegridade(T))
        printf("Teste Remocao Caso 1 (irmao vermelho): OK\n");
    else
        printf("Teste Remocao Caso 1 (irmao vermelho): FALHA\n");
}


void testeRemocaoCaso2(void) {
    ArvoreRB *T = criarArvoreRB();

    /*
        Estrutura antes da remoção:
                10(B)
               /     \
            5(B)     15(B)
           /
        1(R)

        Remoção de 1 força Caso 2:
        irmão preto com filhos pretos
    */

    RB_insert(T, 10);
    RB_insert(T, 5);
    RB_insert(T, 15);
    RB_insert(T, 1);

    RB_delete(T, 1);

    if (verificarIntegridade(T))
        printf("Teste Remocao Caso 2 (irmao preto, filhos pretos): OK\n");
    else
        printf("Teste Remocao Caso 2 (irmao preto, filhos pretos): FALHA\n");
}


void testeRemocaoCaso3(void) {
    ArvoreRB *T = criarArvoreRB();

    /*
        Estrutura antes da remoção:
                10(B)
               /     \
            5(B)     20(B)
                    /
                 15(R)

        Remoção de 5 força Caso 3
        (irmao preto, filho interno vermelho)
    */

    RB_insert(T, 10);
    RB_insert(T, 5);
    RB_insert(T, 20);
    RB_insert(T, 15);

    RB_delete(T, 5);

    if (verificarIntegridade(T))
        printf("Teste Remocao Caso 3 (filho interno vermelho): OK\n");
    else
        printf("Teste Remocao Caso 3 (filho interno vermelho): FALHA\n");
}

void testeRemocaoCaso4(void) {
    ArvoreRB *T = criarArvoreRB();

    /*
        Estrutura antes da remoção:
                10(B)
               /     \
            5(B)     20(B)
                        \
                        25(R)

        Remoção de 5 força Caso 4
        (irmao preto, filho externo vermelho)
    */

    RB_insert(T, 10);
    RB_insert(T, 5);
    RB_insert(T, 20);
    RB_insert(T, 25);

    RB_delete(T, 5);

    if (verificarIntegridade(T))
        printf("Teste Remocao Caso 4 (filho externo vermelho): OK\n");
    else
        printf("Teste Remocao Caso 4 (filho externo vermelho): FALHA\n");
}
