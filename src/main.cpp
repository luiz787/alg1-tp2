#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include "Ilha.hpp"

std::ifstream abrirArquivoEntrada(char** argv);
void resolverViaAlgoritmoGuloso(uint32_t custoMaximo, std::vector<Ilha> &ilhas);
void resolverViaProgramacaoDinamica(uint32_t custoMaximo, std::vector<Ilha> &ilhas);
std::vector<Ilha> lerEntrada(std::ifstream &arquivoEntrada, uint32_t quantidadeIlhas);

/*
 * Função utilizada para ordenação: ordem decrescente pelo custo benefício.
 */
bool compararIlhasPorCustoBeneficio(const Ilha& a, const Ilha& b) {
    return a.getCustoBeneficio() > b.getCustoBeneficio();
}

int main(int argc, char**argv) {
    auto arquivoEntrada = abrirArquivoEntrada(argv);
    uint32_t custoMaximo;
    uint32_t quantidadeIlhas;
    arquivoEntrada >> custoMaximo >> quantidadeIlhas;
    std::vector<Ilha> ilhas = lerEntrada(arquivoEntrada, quantidadeIlhas);

    resolverViaAlgoritmoGuloso(custoMaximo, ilhas);
    resolverViaProgramacaoDinamica(custoMaximo, ilhas);

    return 0;
}

std::ifstream abrirArquivoEntrada(char** argv) {
    char* inputFileName = argv[1];
    std::ifstream inputFile (inputFileName);
    if (!inputFile.is_open()) {
        throw std::invalid_argument("Falha ao abrir o arquivo de entrada.");
    }
    return inputFile;
}

std::vector<Ilha> lerEntrada(std::ifstream &arquivoEntrada, uint32_t quantidadeIlhas) {
    std::vector<Ilha> ilhas;
    for (uint32_t i = 0; i < quantidadeIlhas; i++) {
        uint32_t custoDiarioIlha;
        uint32_t pontuacaoIlha;
        arquivoEntrada >> custoDiarioIlha >> pontuacaoIlha;
        auto ilha = Ilha(custoDiarioIlha, pontuacaoIlha);
        ilhas.push_back(ilha);
    }
    return ilhas;
}

void resolverViaAlgoritmoGuloso(uint32_t custoMaximo, std::vector<Ilha> &ilhas) {

    // Copia ilhas para um vetor auxiliar, para não gerar efeitos colaterais fora da função ao ordenar.
    auto copiaIlhas = ilhas;

    /*
     * Ordena as ilhas por custo benefício. Função definida da seguinte maneira:
     * f(custo, pontuacao): pontuacao / custo
     */
    std::sort(copiaIlhas.begin(), copiaIlhas.end(), compararIlhasPorCustoBeneficio); // TODO: implementar MergeSort

    uint32_t pontuacaoFinal = 0;
    uint32_t quantidadeDiasViagem = 0;
    uint32_t dinheiroRemanescente = custoMaximo;
    for (const auto &ilha : copiaIlhas) {
        auto quantidadeDiasPossiveisIlha = dinheiroRemanescente / ilha.getCustoDiario();
        pontuacaoFinal += quantidadeDiasPossiveisIlha * ilha.getPontuacaoDiaria();
        quantidadeDiasViagem += quantidadeDiasPossiveisIlha;
        dinheiroRemanescente -= quantidadeDiasPossiveisIlha * ilha.getCustoDiario();
    }
    std::cout << pontuacaoFinal << " " << quantidadeDiasViagem << std::endl;
}

void resolverViaProgramacaoDinamica(uint32_t custoMaximo, std::vector<Ilha> &ilhas) {
    auto quantidadeIlhas = ilhas.size();
    uint32_t tabelaLookup[quantidadeIlhas + 1][custoMaximo + 1];

    for (uint32_t i = 1; i <= quantidadeIlhas; i++) {

        /*
         * Aqui o indice i é normalizado para i - 1, para que se consiga acessar a ilha indexada por 0, visto que a
         * primeira iteração do algortimo de programação dinâmica considera o subconjunto vazio como 0.
         */
        auto ilhaAtual = ilhas[i - 1];
        for (uint32_t custo = 0; custo <= custoMaximo; custo++) {
            if (ilhaAtual.getCustoDiario() > custo) {
                tabelaLookup[i][custo] = tabelaLookup[i - 1][custo];
            } else {
                auto custoSemUtilizarIlhaAtual = tabelaLookup[i - 1][custo];
                auto custoUtilizandoIlhaAtual = ilhaAtual.getPontuacaoDiaria() + tabelaLookup[i - 1][custo - ilhaAtual.getCustoDiario()];
                tabelaLookup[i][custo] = std::max(custoSemUtilizarIlhaAtual, custoUtilizandoIlhaAtual);
            }
        }
    }
    auto pontuacaoMaxima = tabelaLookup[quantidadeIlhas][custoMaximo];

    auto custo = custoMaximo;
    auto dias = 0;

    auto pontuacao = pontuacaoMaxima;
    for (uint32_t i = quantidadeIlhas; i >= 0 && pontuacao > 0; i--) {
        if (tabelaLookup[i][custo] == tabelaLookup[i - 1][custo]) {
            continue;
        } else {
            dias++;
            custo = custo - ilhas[i - 1].getCustoDiario();
            pontuacao = pontuacao - ilhas[i - 1].getPontuacaoDiaria();
        }
    }
    std::cout << pontuacaoMaxima << " " << dias << std::endl;
}