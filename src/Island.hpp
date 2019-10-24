#ifndef ALG1_TP2_ILHA_HPP
#define ALG1_TP2_ILHA_HPP


#include <cstdint>

class Island {
private:
    uint32_t dailyCost;
    uint32_t dailyPunctuation;
public:
    Island() = default;
    Island(Island *pOther);
    Island(uint32_t dailyCost, uint32_t dailyPunctuation);
    ~Island();

    uint32_t getDailyCost() const;
    uint32_t getDailyPunctuation() const;
    double getCostBenefit() const;
};


#endif
