#ifndef ARVORE_RB_H
#define ARVORE_RB_H

typedef enum { VERMELHO, PRETO } Cor;

typedef struct NoRB NoRB;
typedef struct ArvoreRB ArvoreRB;

// Criação
ArvoreRB* criarArvoreRB();
void destruirArvoreRB(ArvoreRB *T);



// Inserção
void RB_insert(ArvoreRB *T, int chave);

// Remoção 
void RB_delete(ArvoreRB *T, int chave);

// Auditoria 
int verificarIntegridade(ArvoreRB *T);


/* Acesso controlado (necessário para o verificador) */
NoRB *getRaiz(ArvoreRB *T);
NoRB *getNil(ArvoreRB *T);

Cor getCor(NoRB *n);
NoRB *getEsq(NoRB *n);
NoRB *getDir(NoRB *n);




#endif
