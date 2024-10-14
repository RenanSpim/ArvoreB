#ifndef VEICULO_H
#define VEICULO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_PLACA 8
#define TAMANHO_MODELO 20
#define TAMANHO_MARCA 20
#define TAMANHO_CATEGORIA 15
#define TAMANHO_STATUS 16
#define DAT_NOME "veiculos.dat"

typedef struct {
    char placa[TAMANHO_PLACA];
    char modelo[TAMANHO_MODELO];
    char marca[TAMANHO_MARCA];
    int ano;
    char categoria[TAMANHO_CATEGORIA];
    int quilometragem;
    char status[TAMANHO_STATUS];
} Veiculo;

typedef struct {
    Veiculo *veiculos;
    int currI;
} FilaVeiculos;

int lerVeiculo(Veiculo *veiculo, int registro); // Lê o veículo na posição registro do arquivo .dat, retorna 1 se foi achado
int adicionarVeiculo(Veiculo *veiculo); // Adiciona veiculo no final do arquivo .dat, retorna a posição que ele foi inserido
int removerVeiculo(int registro); // Remove o veículo na posição registro do arquivo .dat, retorna 1 se foi removido
void printVeiculo(Veiculo veiculo); // Imprime veiculo

#endif
