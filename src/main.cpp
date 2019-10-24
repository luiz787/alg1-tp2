#include <iostream>
#include <fstream>
#include "Island.hpp"
#include "MergeSortIslands.hpp"

std::ifstream openInputFile(int argc, char** argv);
Island* readInput(std::ifstream &inputFile, uint32_t amountOfIslands);

void solveWithGreedyAlgorithm(uint32_t maximumCost, Island* islands, uint32_t amountOfIslands);
void solveWithDynamicProgramming(uint32_t maximumCost, Island* islands, uint32_t amountOfIslands);


int main(int argc, char**argv) {
    auto inputFile = openInputFile(argc, argv);
    uint32_t maximumCost = 0;
    uint32_t amountOfIslands = 0;
    inputFile >> maximumCost >> amountOfIslands;
    auto islands = readInput(inputFile, amountOfIslands);

    solveWithGreedyAlgorithm(maximumCost, islands, amountOfIslands);
    solveWithDynamicProgramming(maximumCost, islands, amountOfIslands);

    delete[] islands;
    return 0;
}

std::ifstream openInputFile(int argc, char** argv) {
    if (argc < 2) {
        throw std::invalid_argument("Nome do arquivo de entrada deve ser passado como argumento.");
    }
    char* inputFileName = argv[1];
    std::ifstream inputFile (inputFileName);
    if (!inputFile.is_open()) {
        throw std::invalid_argument("Falha ao abrir o arquivo de entrada.");
    }
    return inputFile;
}

Island* readInput(std::ifstream &inputFile, uint32_t amountOfIslands) {
    auto islands = new Island[amountOfIslands];
    for (uint32_t i = 0; i < amountOfIslands; i++) {
        uint32_t islandDailyCost;
        uint32_t islandPunctuation;
        inputFile >> islandDailyCost >> islandPunctuation;
        islands[i] = Island(islandDailyCost, islandPunctuation);
    }
    return islands;
}

void solveWithGreedyAlgorithm(uint32_t maximumCost, Island* islands, uint32_t amountOfIslands) {
    /*
     * Ordena as ilhas por custo por ponto. Função definida da seguinte maneira:
     * f(custo, pontuacao): custo / pontucacao.
     * Com isso, as ilhas que tem o menor custo por ponto são as mais vantajosas, com maior
     * "custo benefício".
     */
    MergeSortIslands::sort(islands, amountOfIslands);
    uint32_t finalPunctuation = 0;
    uint32_t tripDurationInDays = 0;
    uint32_t remainderMoney = maximumCost;

    for (uint32_t i = 0; i < amountOfIslands; ++i) {
        auto island = islands[i];
        auto possibleDaysInIsland = remainderMoney / island.getDailyCost();
        finalPunctuation += possibleDaysInIsland * island.getDailyPunctuation();
        tripDurationInDays += possibleDaysInIsland;
        remainderMoney -= possibleDaysInIsland * island.getDailyCost();
    }
    std::cout << finalPunctuation << " " << tripDurationInDays << std::endl;
}

void solveWithDynamicProgramming(uint32_t maximumCost, Island* islands, uint32_t amountOfIslands) {
    uint32_t lookupTable[amountOfIslands + 1][maximumCost + 1];

    // Pré-inicializa valores da tabela de lookup para 0.
    for (uint32_t i = 0; i <= amountOfIslands; i++) {
        for (uint32_t j = 0; j <= maximumCost; j++) {
            lookupTable[i][j] = 0;
        }
    }

    for (uint32_t i = 1; i <= amountOfIslands; i++) {

        /*
         * Aqui o indice i é normalizado para i - 1, para que se consiga acessar a ilha indexada por 0, visto que a
         * primeira iteração do algortimo de programação dinâmica considera o subconjunto vazio como 0.
         */
        auto currentIsland = islands[i - 1];
        for (uint32_t cost = 0; cost <= maximumCost; cost++) {
            if (currentIsland.getDailyCost() > cost) {
                lookupTable[i][cost] = lookupTable[i - 1][cost];
            } else {
                auto costWithoutUsingCurrentIsland = lookupTable[i - 1][cost];
                auto costUsingCurrentIsland = currentIsland.getDailyPunctuation() + lookupTable[i - 1][cost -
                                                                                                       currentIsland.getDailyCost()];
                lookupTable[i][cost] = std::max(costWithoutUsingCurrentIsland, costUsingCurrentIsland);
            }
        }
    }
    auto maximumPunctuation = lookupTable[amountOfIslands][maximumCost];

    auto cost = maximumCost;
    auto days = 0;

    auto punctuation = maximumPunctuation;
    for (uint32_t i = amountOfIslands; i >= 0 && punctuation > 0; i--) {
        if (lookupTable[i][cost] == lookupTable[i - 1][cost]) {
            continue;
        } else {
            days++;
            cost = cost - islands[i - 1].getDailyCost();
            punctuation = punctuation - islands[i - 1].getDailyPunctuation();
        }
    }
    std::cout << maximumPunctuation << " " << days << std::endl;
}
