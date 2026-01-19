#include <stdio.h>
#include "../include/arvore_rb.h"

/* funções externas */
int verificarIntegridade(ArvoreRB *T);
void testeInsercaoCaso1(void);

int main() {
    printf("Teste inicial da arvore vazia:\n");

    ArvoreRB *T = criarArvoreRB();
    if (verificarIntegridade(T))
        printf("Arvore inicial valida\n\n");
    else
        printf("Arvore inicial invalida\n\n");

    printf("Rodando teste de insercao - Caso 1:\n");
    testeInsercaoCaso1();

    return 0;
}
