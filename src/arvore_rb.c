#include <stdio.h>
#include <stdlib.h>
#include "../include/arvore_rb.h"

struct NoRB {
    int chave;
    Cor cor;
    NoRB *esq;
    NoRB *dir;
    NoRB *pai;
};

struct ArvoreRB {
    NoRB *raiz;
    NoRB *Nil;
};

ArvoreRB* criarArvoreRB() {
    ArvoreRB *T = malloc(sizeof(ArvoreRB));

    T->Nil = malloc(sizeof(NoRB));
    T->Nil->cor = PRETO;
    T->Nil->esq = T->Nil;
    T->Nil->dir = T->Nil;
    T->Nil->pai = T->Nil;

    T->raiz = T->Nil;
    return T;
}


void rotacaoEsquerda(ArvoreRB *T, NoRB *x) {
    NoRB *y = x->dir;          // y é o filho direito de x

    x->dir = y->esq;           // subárvore esquerda de y vira direita de x
    if (y->esq != T->Nil) {
        y->esq->pai = x;
    }

    y->pai = x->pai;           // liga y ao antigo pai de x

    if (x->pai == T->Nil) {
        T->raiz = y;           // x era raiz
    }
    else if (x == x->pai->esq) {
        x->pai->esq = y;
    }
    else {
        x->pai->dir = y;
    }

    y->esq = x;                // x vira filho esquerdo de y
    x->pai = y;
}


void rotacaoDireita(ArvoreRB *T, NoRB *y) {
    NoRB *x = y->esq;          // x é o filho esquerdo de y

    y->esq = x->dir;           // subárvore direita de x vira esquerda de y
    if (x->dir != T->Nil) {
        x->dir->pai = y;
    }

    x->pai = y->pai;           // liga x ao antigo pai de y

    if (y->pai == T->Nil) {
        T->raiz = x;           // y era raiz
    }
    else if (y == y->pai->dir) {
        y->pai->dir = x;
    }
    else {
        y->pai->esq = x;
    }

    x->dir = y;                // y vira filho direito de x
    y->pai = x;
}

// Cria um novo nó vermelho
NoRB* criarNo(ArvoreRB *T, int chave) {
    NoRB *novo = (NoRB*) malloc(sizeof(NoRB));
    novo->chave = chave;
    novo->cor = VERMELHO;      // todo nó novo nasce vermelho
    novo->esq = T->Nil;
    novo->dir = T->Nil;
    novo->pai = T->Nil;
    return novo;
}

void RB_insert(ArvoreRB *T, int chave) {
    NoRB *z = criarNo(T, chave);

    NoRB *y = T->Nil;      // pai de z
    NoRB *x = T->raiz;     // começa pela raiz

    // Inserção padrão de ABB
    while (x != T->Nil) {
        y = x;
        if (z->chave < x->chave)
            x = x->esq;
        else
            x = x->dir;
    }

    z->pai = y;

    if (y == T->Nil)
        T->raiz = z;              // árvore estava vazia
    else if (z->chave < y->chave)
        y->esq = z;
    else
        y->dir = z;

    // Correção das propriedades Red-Black
    RB_insert_fixup(T, z);
}

void RB_insert_fixup(ArvoreRB *T, NoRB *z) {
    while (z->pai->cor == VERMELHO) {

        // Pai é filho esquerdo
        if (z->pai == z->pai->pai->esq) {
            NoRB *y = z->pai->pai->dir;  // tio

            // CASO 1 — tio vermelho
            if (y->cor == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            }
            else {
                // CASO 2 — tio preto e z é filho direito
                if (z == z->pai->dir) {
                    z = z->pai;
                    rotacaoEsquerda(T, z);
                }

                // CASO 3 — tio preto e z é filho esquerdo
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoDireita(T, z->pai->pai);
            }
        }

        // Pai é filho direito (caso simétrico)
        else {
            NoRB *y = z->pai->pai->esq;  // tio

            // CASO 1 (simétrico)
            if (y->cor == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            }
            else {
                // CASO 2 (simétrico)
                if (z == z->pai->esq) {
                    z = z->pai;
                    rotacaoDireita(T, z);
                }

                // CASO 3 (simétrico)
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoEsquerda(T, z->pai->pai);
            }
        }
    }

    // Garante propriedade da raiz
    T->raiz->cor = PRETO;
}
