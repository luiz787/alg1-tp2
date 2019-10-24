#include "Island.hpp"
#include <iostream>

Island::~Island() = default;

Island::Island(Island *pOther) {
    this->dailyCost = pOther->dailyCost;
    this->dailyPunctuation = pOther->dailyPunctuation;
}

Island::Island(uint32_t dailyCost, uint32_t dailyPunctuation) : dailyCost(dailyCost), dailyPunctuation(dailyPunctuation) {}

uint32_t Island::getDailyCost() const {
    return dailyCost;
}

uint32_t Island::getDailyPunctuation() const {
    return dailyPunctuation;
}

double Island::getCostPerPoint() const {
    return dailyCost / (double) dailyPunctuation;
}
