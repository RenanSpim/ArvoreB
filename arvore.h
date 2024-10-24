#ifndef ARVORE_H
#define ARVORE_H

#include "veiculo.h"

#define IDX_NOME "btree_M.idx"
#define TAMANHO_CABECALHO 64
#define M 5
#define P 10

typedef struct {
    char chaves[M - 1][TAMANHO_PLACA];
    int rnnsDat[M - 1];
    int filhos[M];
    char naFila;
    int qtdChaves;
} Pagina;

int getCabecalhoM(); // Retorna o M armazenado no cabeçalho
int getCabecalhoRaiz(); // Retorna o RRN da raiz no cabeçalho
void criarArvore(FilaVeiculos *fila); // Escreve a árvore no arquivo .idx a partir do arquivo .dat
int adicionarChave(char chave[TAMANHO_PLACA]); // Adiciona um registro na árvore
int buscarChave(char chave[TAMANHO_PLACA]); // Busca a chave chave e retorna o rrn do arquivo .dat
int removerChave(char chave[TAMANHO_PLACA]); // Remove a chave chave do arquivo .dat

#endif
