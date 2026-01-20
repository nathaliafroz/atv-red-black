#include <stdio.h>
#include <stdlib.h>
#include "../include/arvore_rb.h"

/* protótipos internos (uso apenas neste arquivo) */
static void rotacaoEsquerda(ArvoreRB *T, NoRB *x);
static void rotacaoDireita(ArvoreRB *T, NoRB *y);

static void RB_insert_fixup(ArvoreRB *T, NoRB *z);

static void RB_delete_fixup(ArvoreRB *T, NoRB *x);
static void transplantRB(ArvoreRB *T, NoRB *u, NoRB *v);
static NoRB* treeMinimum(ArvoreRB *T, NoRB *x);



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

/* Funções de acesso */
NoRB *getRaiz(ArvoreRB *T) { return T->raiz; }
NoRB *getNil(ArvoreRB *T) { return T->Nil; }

Cor getCor(NoRB *n) { return n->cor; }
NoRB *getEsq(NoRB *n) { return n->esq; }
NoRB *getDir(NoRB *n) { return n->dir; }

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


static void rotacaoEsquerda(ArvoreRB *T, NoRB *x) {
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


static void rotacaoDireita(ArvoreRB *T, NoRB *y) {
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


//Funções auxiliares (internas)
static NoRB* treeMinimum(ArvoreRB *T, NoRB *x) {
    while (x->esq != T->Nil)
        x = x->esq;
    return x;
}

static void transplantRB(ArvoreRB *T, NoRB *u, NoRB *v) {
    if (u->pai == T->Nil)
        T->raiz = v;
    else if (u == u->pai->esq)
        u->pai->esq = v;
    else
        u->pai->dir = v;

    v->pai = u->pai;
}

//Função principal de remoção

void RB_delete(ArvoreRB *T, int chave) {
    NoRB *z = T->raiz;

    // busca do nó
    while (z != T->Nil && z->chave != chave) {
        if (chave < z->chave)
            z = z->esq;
        else
            z = z->dir;
    }

    if (z == T->Nil)
        return; // chave não encontrada

    NoRB *y = z;
    Cor corOriginal = y->cor;
    NoRB *x;

    if (z->esq == T->Nil) {
        x = z->dir;
        transplantRB(T, z, z->dir);
    }
    else if (z->dir == T->Nil) {
        x = z->esq;
        transplantRB(T, z, z->esq);
    }
    else {
        y = treeMinimum(T, z->dir);
        corOriginal = y->cor;
        x = y->dir;

        if (y->pai == z)
            x->pai = y;
        else {
            transplantRB(T, y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }

        transplantRB(T, z, y);
        y->esq = z->esq;
        y->esq->pai = y;
        y->cor = z->cor;
    }

    if (corOriginal == PRETO)
        RB_delete_fixup(T, x);
}

static void RB_delete_fixup(ArvoreRB *T, NoRB *x) {
    while (x != T->raiz && x->cor == PRETO) {

        // x é filho esquerdo
        if (x == x->pai->esq) {
            NoRB *w = x->pai->dir; // irmão

            // CASO 1 — irmão vermelho
            if (w->cor == VERMELHO) {
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacaoEsquerda(T, x->pai);
                w = x->pai->dir;
            }

            // CASO 2 — irmão preto, filhos pretos
            if (w->esq->cor == PRETO && w->dir->cor == PRETO) {
                w->cor = VERMELHO;
                x = x->pai;
            }
            else {
                // CASO 3 — irmão preto, filho esquerdo vermelho
                if (w->dir->cor == PRETO) {
                    w->esq->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacaoDireita(T, w);
                    w = x->pai->dir;
                }

                // CASO 4 — irmão preto, filho direito vermelho
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->dir->cor = PRETO;
                rotacaoEsquerda(T, x->pai);
                x = T->raiz;
            }
        }

        // CASOS SIMÉTRICOS
        else {
            NoRB *w = x->pai->esq;

            if (w->cor == VERMELHO) {
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacaoDireita(T, x->pai);
                w = x->pai->esq;
            }

            if (w->dir->cor == PRETO && w->esq->cor == PRETO) {
                w->cor = VERMELHO;
                x = x->pai;
            }
            else {
                if (w->esq->cor == PRETO) {
                    w->dir->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacaoEsquerda(T, w);
                    w = x->pai->esq;
                }

                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->esq->cor = PRETO;
                rotacaoDireita(T, x->pai);
                x = T->raiz;
            }
        }
    }

    x->cor = PRETO;
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




