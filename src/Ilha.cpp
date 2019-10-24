#include "Ilha.hpp"

Ilha::~Ilha() = default;

Ilha::Ilha(Ilha *pIlha) {
    this->custoDiario = pIlha->custoDiario;
    this->pontuacaoDiaria = pIlha->pontuacaoDiaria;
}

Ilha::Ilha(uint32_t custoDiario, uint32_t pontuacaoDiaria) : custoDiario(custoDiario), pontuacaoDiaria(pontuacaoDiaria) {}

uint32_t Ilha::getCustoDiario() const {
    return custoDiario;
}

uint32_t Ilha::getPontuacaoDiaria() const {
    return pontuacaoDiaria;
}

double Ilha::getCustoBeneficio() const {
    return pontuacaoDiaria / (double) custoDiario;
}
