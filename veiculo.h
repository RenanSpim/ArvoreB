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
    int i;
} FilaVeiculos;

size_t lerRegistroDat(Veiculo *veiculoArr, int registro);
void printRegistro(Veiculo veiculo);

#endif
