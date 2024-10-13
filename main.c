#include "veiculo.h"
#include "arvore.h"

int main() {
    FilaVeiculos fila;
    fila.i = -1;
    fila.veiculos = malloc(sizeof(Veiculo) * P);

    if (fopen(NOME_DAT, "rd") == NULL) return 1;

    if (!abrirArvore(NOME_IDX) || getCabecalhoM() != M) {
        escreverCabecalho(0);
        criarArvore(&fila);
    } else {
        lerCabecalho();
    }

    return 0;
}