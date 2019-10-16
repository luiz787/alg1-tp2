#include "Ilha.hpp"

Ilha::Ilha(uint32_t custoDiario, uint32_t pontuacaoDiaria) : custoDiario(custoDiario), pontuacaoDiaria(pontuacaoDiaria) {
    this->custoBeneficio = pontuacaoDiaria / (double) custoDiario;
}

Ilha::~Ilha() = default;

uint32_t Ilha::getCustoDiario() const {
    return custoDiario;
}

uint32_t Ilha::getPontuacaoDiaria() const {
    return pontuacaoDiaria;
}

double Ilha::getCustoBeneficio() const {
    return custoBeneficio;
}
