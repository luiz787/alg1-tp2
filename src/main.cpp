#include <iostream>
#include <vector>
#include <fstream>

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
    std::vector<uint32_t> custosIlhas(quantidadeIlhas);
    std::vector<uint32_t> pontuacoesIlhas(quantidadeIlhas);
    for (uint32_t i = 0; i < quantidadeIlhas; i++) {
        uint32_t custoDiarioIlha;
        uint32_t pontuacaoIlha;
        inputFile >> custoDiarioIlha >> pontuacaoIlha;
        custosIlhas[i] = custoDiarioIlha;
        pontuacoesIlhas[i] = pontuacaoIlha;
    }

    // TODO: remover testes de entrada.
    std::cout << "Custos: " << std::endl;
    for (auto c : custosIlhas) {
        std::cout << c << std::endl;
    }
    std::cout << "Pontuacoes: " << std::endl;
    for (auto c : pontuacoesIlhas) {
        std::cout << c << std::endl;
    }
    return 0;
}