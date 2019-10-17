#ifndef ALG1_TP2_ILHA_HPP
#define ALG1_TP2_ILHA_HPP


#include <cstdint>

class Ilha {
private:
    uint32_t custoDiario;
    uint32_t pontuacaoDiaria;
public:
    Ilha() = default;
    Ilha(uint32_t custoDiario, uint32_t pontuacaoDiaria);
    ~Ilha();

    uint32_t getCustoDiario() const;
    uint32_t getPontuacaoDiaria() const;
    double getCustoBeneficio() const;
};


#endif
