#ifndef ARVORE_H
#define ARVORE_H

#include "veiculo.h"

#define IDX_NOME "btree_M.idx"
#define TAMANHO_CABECALHO 64
#define M 5
#define P 10

typedef struct {
    char chaves[M - 1][TAMANHO_PLACA];
    int rnns[M + 1]; // rnns[0] == rnn do pai
    char naFila;
} Pagina;

size_t abrirArvore();
int lerCabecalho();
int escreverCabecalho(int raiz);
void criarArvore(FilaVeiculos *fila);
int inserirPagina();
Pagina lerPagina(int rrn);
int getCabecalhoM();

#endif
