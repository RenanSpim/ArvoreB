#include "veiculo.h"
#include "arvore.h"

int main() {
    FilaVeiculos fila;
    fila.currI = -1;
    fila.veiculos = malloc(sizeof(Veiculo) * P);

    criarArvore(&fila);
    printf("M: %d, RRN: %d\n", getCabecalhoM(), getCabecalhoRaiz());
    // for (int i = 0; i < P; i++) printVeiculo(fila.veiculos[i]);
    return 0;
}