#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

int rrnRaiz = 0;

int getCabecalhoM();
int getCabecalhoRaiz();
void dividirPagina(int rrn, char chave[TAMANHO_PLACA]);
void escreverCabecalho(FILE *file);
void criarArvore(FilaVeiculos *fila);
void lerPagina(int rrn, Pagina *pagina);
void escreverPaginaNoDisco(int rrn, Pagina *pagina);
void inserirNaPagina(Pagina *pagina, char chave[TAMANHO_PLACA]);
void promoverChave(char chave[TAMANHO_PLACA], int rrn1, int rrn2);
void dividirPagina(int rrn, char chave[TAMANHO_PLACA]);
int buscarIndice(char chave[TAMANHO_PLACA], Pagina *pagina);
int geraRrnPaginas();
int buscarPaginaInsercao(char chave[TAMANHO_PLACA], Pagina *pagina);
int adicionarChave(char chave[TAMANHO_PLACA]);
int buscarChave(char chave[TAMANHO_PLACA]);

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

int buscarIndice(char chave[TAMANHO_PLACA], Pagina *pagina) {
    for (int i = 0; i < pagina->qtdChaves; i++) {
        if (strcmp(chave, pagina->chaves[i]) < 0) {
            return i;
        }
    }

    return pagina->qtdChaves;
}

void lerPagina(int rrn, Pagina *pagina) {
    FILE *file = fopen(IDX_NOME, "rb+");

    if (!file) {
        perror("Erro ao ler pagina no disco");
        return;
    }

    fseek(file, TAMANHO_CABECALHO + rrn * sizeof(Pagina), SEEK_SET);
    fread(pagina, sizeof(Pagina), 1, file);
    fclose(file);
}

void escreverPaginaNoDisco(int rrn, Pagina *pagina) {
    FILE *file = fopen(IDX_NOME, "rb+");

    if (!file) {
        perror("Erro ao escrever pagina no disco");
        return;
    }

    fseek(file, TAMANHO_CABECALHO + rrn * sizeof(Pagina), SEEK_SET);
    fwrite(pagina, sizeof(Pagina), 1, file);
    fclose(file);
}

int geraRrnPaginas() {
    FILE *file = fopen(IDX_NOME, "rb+");

    if (!file) {
        perror("Erro ao gerar o rrn da pagina");
        return -1;
    }

    int rrn;
    fseek(file, 0, SEEK_END);

    rrn = (ftell(file) - TAMANHO_CABECALHO) / sizeof(Pagina);

    fclose(file);

    return rrn;
}

int buscarPaginaInsercao(char chave[TAMANHO_PLACA], Pagina *pagina) {
    int rrnPagina = rrnRaiz;

    while (rrnPagina != -1) {
        lerPagina(rrnPagina, pagina);

        int i = 0;
        for (; i < pagina->qtdChaves; i++) {
            if (strcmp(chave, pagina->chaves[i]) < 0) {
                break;
            }
        }

        if (pagina->filhos[0] == -1) {
            return rrnPagina;
        }

        rrnPagina = pagina->filhos[i];
    }

    perror("Erro na busca pagina insercao (sem raiz?)");

    return rrnPagina;
}

void inserirNaPagina(Pagina *pagina, char chave[TAMANHO_PLACA]) {
    int i = pagina->qtdChaves - 1;
    char chaveAux[TAMANHO_PLACA];

    while (i >= 0 && strcmp(chave, pagina->chaves[i]) < 0) {
        strcpy(pagina->chaves[i + 1], pagina->chaves[i]);
        pagina->filhos[i + 1] = pagina->filhos[i];

        i--;
    }

    strcpy(pagina->chaves[i + 1], chave);

    pagina->qtdChaves++;
}

void promoverChave(char chave[TAMANHO_PLACA], int rrn1, int rrn2) {
    Pagina paginaPai;
    int rrnPai = getCabecalhoRaiz();

    if (rrnPai == -1) {
        Pagina novaRaiz;

        novaRaiz.qtdChaves = 1;
        strcpy(novaRaiz.chaves[0], chave);
        novaRaiz.filhos[0] = rrn1;
        novaRaiz.filhos[1] = rrn2;
        novaRaiz.naFila = 0;

        rrnRaiz = geraRrnPaginas();
        escreverPaginaNoDisco(rrnRaiz, &novaRaiz);

        return;
    }

    buscarPaginaInsercao(chave, &paginaPai);

    if (paginaPai.qtdChaves < M - 1) {
        int index = buscarIndice(chave, &paginaPai);
        inserirNaPagina(&paginaPai, chave);
        paginaPai.filhos[index] = rrn1;
        paginaPai.filhos[index + 1] = rrn2;
        escreverPaginaNoDisco(rrnPai, &paginaPai);
    } else {
        dividirPagina(rrnPai, chave);
    }
}

void dividirPagina(int rrn, char chave[TAMANHO_PLACA]) {
    Pagina pagina, novaPagina;
    int i, meio = M / 2, filhos[M + 1];
    char chaves[M][TAMANHO_PLACA];

    novaPagina.qtdChaves = 0;
    novaPagina.naFila = 0;

    lerPagina(rrn, &pagina);

    for (i = 0; i < M - 1; i++) {
        strcpy(chaves[i], pagina.chaves[i]);
        filhos[i] = pagina.filhos[i];
    }
    filhos[M - 1] = pagina.filhos[M - 1];

    i = M - 2;
    while (i >= 0 && strcmp(chave, chaves[i]) < 0) {
        strcpy(chaves[i + 1], chaves[i]);
        filhos[i + 2] = filhos[i + 1];

        i--;
    }
    strcpy(chaves[i + 1], chave);

    for (i = meio + 1; i < M; i++) {
        strcpy(novaPagina.chaves[i - meio - 1], chaves[i]);
        novaPagina.filhos[i - meio - 1] = filhos[i];
        novaPagina.qtdChaves++;
    }
    novaPagina.filhos[novaPagina.qtdChaves] = filhos[M];

    pagina.qtdChaves = meio;
    for (i = 0; i < meio; i++) {
        strcpy(pagina.chaves[i], chaves[i]);
        pagina.filhos[i] = filhos[i];
    }

    int novoRrn = geraRrnPaginas();

    escreverPaginaNoDisco(novoRrn, &novaPagina);
    escreverPaginaNoDisco(rrn, &pagina);

    promoverChave(chaves[meio], rrn, novoRrn);
}

int adicionarChave(char chave[TAMANHO_PLACA]) {
    Pagina pagina;
    int rrnPagina = buscarPaginaInsercao(chave, &pagina);
    
    if (pagina.qtdChaves < M - 1) { // maximo de chaves
        inserirNaPagina(&pagina, chave);
        escreverPaginaNoDisco(rrnPagina, &pagina);
    } else {
        dividirPagina(rrnPagina, chave);
    }
    
    return 1;
}

int buscarChave(char chave[TAMANHO_PLACA]) {
    Pagina pagina;
    int rrnPagina = rrnRaiz;
    
    while (rrnPagina != -1) {
        lerPagina(rrnPagina, &pagina);
        
        for (int i = 0; i < pagina.qtdChaves; i++) {
            if (strcmp(chave, pagina.chaves[i]) == 0) {
                return rrnPagina;
            } else if (strcmp(chave, pagina.chaves[i]) < 0) {
                rrnPagina = pagina.filhos[i];
                break;
            }
        }
        
        rrnPagina = pagina.filhos[pagina.qtdChaves];
    }
    
    return -1;
}
