#include "Island.hpp"

Island::~Island() = default;

Island::Island(const uint32_t dailyCost, const uint32_t dailyPunctuation) : dailyCost(dailyCost), dailyPunctuation(dailyPunctuation) {}

uint32_t Island::getDailyCost() const {
    return dailyCost;
}

uint32_t Island::getDailyPunctuation() const {
    return dailyPunctuation;
}

double Island::getCostPerPoint() const {
    return dailyCost / (double) dailyPunctuation;
}
