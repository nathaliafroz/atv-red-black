#include <stdio.h>
#include "../include/arvore_rb.h"

/* funções externas (definidas em teste_rb.c) */
int verificarIntegridade(ArvoreRB *T);

void testeInsercaoCaso1(void);
void testeInsercaoCaso2(void);
void testeInsercaoCaso3(void);

void testeRemocaoNoVermelho(void);

void testeRemocaoCaso1(void);
void testeRemocaoCaso2(void);
void testeRemocaoCaso3(void);
void testeRemocaoCaso4(void);

int main() {

    printf("Teste inicial da arvore vazia:\n");

    ArvoreRB *T = criarArvoreRB();
    if (verificarIntegridade(T))
        printf("Arvore inicial valida\n\n");
    else
        printf("Arvore inicial invalida\n\n");

    printf("Rodando testes de insercao:\n\n");

    printf("Caso 1 (tio vermelho):\n");
    testeInsercaoCaso1();

    printf("\nCaso 2 (rotacao simples):\n");
    testeInsercaoCaso2();

    printf("\nCaso 3 (rotacao final):\n");
    testeInsercaoCaso3();

    printf("\nTeste Remocao - No Vermelho:\n");
    testeRemocaoNoVermelho();

    printf("\nCaso 1 da Remocao (irmao vermelho):\n");
    testeRemocaoCaso1();

    printf("\nCaso 2 da Remocao (irmao preto, filhos pretos):\n");
    testeRemocaoCaso2();

    printf("\nCaso 3 da Remocao (filho interno vermelho):\n");
    testeRemocaoCaso3();

    printf("\nCaso 4 da Remocao (filho externo vermelho):\n");testeRemocaoCaso4();


    return 0;
}
