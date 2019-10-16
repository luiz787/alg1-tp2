#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include "Ilha.hpp"

void resolverViaAlgoritmoGuloso(uint32_t custoMaximo, std::vector<Ilha> &ilhas);
std::vector<Ilha> lerEntrada(std::ifstream &inputFile, uint32_t quantidadeIlhas);

/*
 * Função utilizada para ordenação: ordem decrescente pelo custo benefício.
 */
bool compararIlhas(Ilha a, Ilha b) {
    return a.getCustoBeneficio() > b.getCustoBeneficio();
}

int main(int argc, char**argv) {
    char* inputFileName = argv[1];
    std::ifstream inputFile (inputFileName);
    if (!inputFile.is_open()) {
        std::cout << "Falha ao abrir o arquivo de entrada." << std::endl;
        return 1;
    }
    uint32_t custoMaximo;
    uint32_t quantidadeIlhas;
    inputFile >> custoMaximo >> quantidadeIlhas;
    std::vector<Ilha> ilhas = lerEntrada(inputFile, quantidadeIlhas);

    resolverViaAlgoritmoGuloso(custoMaximo, ilhas);

    return 0;
}

std::vector<Ilha> lerEntrada(std::ifstream &inputFile, uint32_t quantidadeIlhas) {
    std::vector<Ilha> ilhas;
    for (uint32_t i = 0; i < quantidadeIlhas; i++) {
        uint32_t custoDiarioIlha;
        uint32_t pontuacaoIlha;
        inputFile >> custoDiarioIlha >> pontuacaoIlha;
        auto ilha = Ilha(custoDiarioIlha, pontuacaoIlha);
        ilhas.push_back(ilha);
    }
    return ilhas;
}

void resolverViaAlgoritmoGuloso(uint32_t custoMaximo, std::vector<Ilha> &ilhas) {

    /*
     * Ordena as ilhas por custo benefício. Função definida da seguinte maneira:
     * f(custo, pontuacao): pontuacao / custo
     */
    std::sort(ilhas.begin(), ilhas.end(), compararIlhas); // TODO: implementar MergeSort

    uint32_t pontuacaoFinal = 0;
    uint32_t quantidadeDiasViagem = 0;
    uint32_t dinheiroRemanescente = custoMaximo;
    for (const auto &il : ilhas) {
        auto quantidadeDiasPossiveisIlha = dinheiroRemanescente / il.getCustoDiario();
        pontuacaoFinal += quantidadeDiasPossiveisIlha * il.getPontuacaoDiaria();
        quantidadeDiasViagem += quantidadeDiasPossiveisIlha;
        dinheiroRemanescente -= quantidadeDiasPossiveisIlha * il.getCustoDiario();
    }
    std::cout << pontuacaoFinal << " " << quantidadeDiasViagem << std::endl;
}