#include <stdio.h>
#include "../include/arvore_rb.h"

/* Função auxiliar:
   Retorna a altura preta se válida, ou -1 se violação */
static int verificarNo(NoRB *no, NoRB *Nil) {
    if (no == Nil)
        return 1; // Nil conta como preto

    /* Propriedade vermelha */
    if (getCor(no) == VERMELHO) {
        if (getCor(getEsq(no)) == VERMELHO ||
            getCor(getDir(no)) == VERMELHO) {
            return -1;
        }
    }

    int hbEsq = verificarNo(getEsq(no), Nil);
    int hbDir = verificarNo(getDir(no), Nil);

    if (hbEsq == -1 || hbDir == -1)
        return -1;

    /* Black-height deve ser igual */
    if (hbEsq != hbDir)
        return -1;

    return hbEsq + (getCor(no) == PRETO ? 1 : 0);
}

int verificarIntegridade(ArvoreRB *T) {
    NoRB *raiz = getRaiz(T);
    NoRB *Nil = getNil(T);

    /* Regra 1: raiz preta */
    if (getCor(raiz) != PRETO) {
        printf("Violacao: raiz nao e preta\n");
        return 0;
    }

    /* Regra 1: Nil preto */
    if (getCor(Nil) != PRETO) {
        printf("Violacao: Nil nao e preto\n");
        return 0;
    }

    if (verificarNo(raiz, Nil) == -1) {
        printf("Violacao nas propriedades da Red-Black Tree\n");
        return 0;
    }

    return 1; // Árvore válida
}