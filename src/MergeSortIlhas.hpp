#ifndef ALG1_TP2_MERGESORTILHAS_HPP
#define ALG1_TP2_MERGESORTILHAS_HPP

#include "Ilha.hpp"

class MergeSortIlhas {
public:
    static void sort(Ilha islands[], uint32_t size);
private:
    static void mergeSort(Ilha islands[], uint32_t left, uint32_t right);
    static void merge(Ilha islands[], uint32_t left, uint32_t middle, uint32_t right);
};

#endif
