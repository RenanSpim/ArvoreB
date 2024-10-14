#include "veiculo.h"

int lerVeiculo(Veiculo *veiculo, int registro) {
    FILE *file = fopen(DAT_NOME, "rb");

    if (!file) {
        perror("Erro ao abrir o arquivo rb .dat");
        return 0;
    }

    fseek(file, registro * sizeof(Veiculo), SEEK_SET);
    size_t read = fread(veiculo, sizeof(Veiculo), 1, file);

    fclose(file);
    return read == 1;
}

int adicionarVeiculo(Veiculo *veiculo) {
    FILE *file = fopen(DAT_NOME, "ab");

    if (!file) {
        perror("Erro ao abrir o arquivo ab .dat");
        return -1;
    }

    size_t written = fwrite(veiculo, sizeof(Veiculo), 1, file);
    fclose(file);

    return written == 1 ? (int)(ftell(file) / sizeof(Veiculo)) - 1 : -1;
}

int removerVeiculo(int registro) {

}

void printVeiculo(Veiculo veiculo) {
    // printf("Registro de RNN 0\n");
    printf("Placa: %s\n", veiculo.placa);
    printf("Modelo: %s\n", veiculo.modelo);
    printf("Marca: %s\n", veiculo.marca);
    printf("Ano: %d\n", veiculo.ano);
    printf("Categoria: %s\n", veiculo.categoria);
    printf("Quilometragem: %d\n", veiculo.quilometragem);
    printf("Status: %s\n", veiculo.status);
    printf("---------------------------\n");
}
