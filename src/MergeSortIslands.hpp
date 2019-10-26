#ifndef ALG1_TP2_MERGESORTISLANDS_HPP
#define ALG1_TP2_MERGESORTISLANDS_HPP

#include "Island.hpp"

class MergeSortIslands {
public:
    static void sort(Island islands[], uint32_t size);
private:

    // Construtor privado para prevenir instanciação de classe estática.
    MergeSortIslands() = default;

    static void mergeSort(Island islands[], uint32_t left, uint32_t right);
    static void merge(Island islands[], uint32_t left, uint32_t middle, uint32_t right);
};

#endif
