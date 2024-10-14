#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

int rrnRaiz = 0;

int getCabecalhoM() {
    FILE *file = fopen(IDX_NOME, "rb");
    int m;

    fseek(file, 0, SEEK_SET);
    fread(&m, sizeof(int), 1, file);
    fclose(file);

    return m;
}

int getCabecalhoRaiz() {
    FILE *file = fopen(IDX_NOME, "rb");

    fseek(file, sizeof(int), SEEK_SET);
    fread(&rrnRaiz, sizeof(int), 1, file);
    fclose(file);

    return rrnRaiz;
}

void escreverCabecalho(FILE *file) {
    int m = M;
    fwrite(&m, sizeof(int), 1, file);
    fwrite(&rrnRaiz, sizeof(int), 1, file);
}

void criarArvore(FilaVeiculos *fila) {
    FILE *file = fopen(IDX_NOME, "wb");
    FILE *datFile = fopen(DAT_NOME, "rb");
    int currI = -1, curr = 0;

    if (!file) {
        perror("Erro ao criar o arquivo wb .idx");
        return;
    } else if (!datFile) {
        perror("Erro ao criar o arquivo rb .dat");
        return;
    }

    escreverCabecalho(file);

    while (fread(&fila->veiculos[++currI], sizeof(Veiculo), 1, datFile)) {
        if (lerVeiculo(&fila->veiculos[currI], curr)) {
            adicionarChave(fila->veiculos[currI].placa);
            curr++;
            if (currI == P - 1) currI = -1;
        } else {
            printf("%d nao foi encontrado por algum motivo (provavelmente foi removido)\n", curr);
        }
    }

    fclose(file);
}

int adicionarChave(char chave[TAMANHO_PLACA]) {
    return 1;
}

int buscarChave(char chave[TAMANHO_PLACA]) {
    return 1;
}
