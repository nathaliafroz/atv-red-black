#ifndef ARVORE_RB_H
#define ARVORE_RB_H

typedef enum { VERMELHO, PRETO } Cor;

typedef struct NoRB NoRB;
typedef struct ArvoreRB ArvoreRB;

// Criação
ArvoreRB* criarArvoreRB();

// Operações estruturais
void rotacaoEsquerda(ArvoreRB *T, NoRB *x);
void rotacaoDireita(ArvoreRB *T, NoRB *y);

// Inserção
void RB_insert(ArvoreRB *T, int chave);

// Remoção (ainda não implementada)
void RB_remove(ArvoreRB *T, int chave);

// Auditoria (ainda não implementada)
int verificarIntegridade(ArvoreRB *T);

#endif
