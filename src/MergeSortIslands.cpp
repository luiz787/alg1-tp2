#include <vector>
#include "MergeSortIslands.hpp"

void MergeSortIslands::sort(Island islands[], uint32_t size) {
    mergeSort(islands, 0, size - 1);
}

void MergeSortIslands::mergeSort(Island islands[], uint32_t left, uint32_t right) {
    if (left < right) {
        uint32_t middle = left + (right - left) / 2;
        mergeSort(islands, left, middle);
        mergeSort(islands, middle + 1, right);
        merge(islands, left, middle, right);
    }
}

void MergeSortIslands::merge(Island islands[], uint32_t left, uint32_t middle, uint32_t right) {
    uint32_t leftSize = middle - left + 1;
    uint32_t rightSize = right - middle;

    Island tempLeft[leftSize];
    Island tempRight[rightSize];
    for (uint32_t i = 0; i < middle - left + 1; i++) {
        tempLeft[i] = islands[left + i];
    }
    for (uint32_t j = 0; j < right - middle; j++) {
        tempRight[j] = islands[middle + 1 + j];
    }
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t addedElements = left;
    while (i < leftSize && j < rightSize) {
        if (tempLeft[i].getCostPerPoint() < tempRight[j].getCostPerPoint()) {
            islands[addedElements++] = tempLeft[i++];
        } else {
            islands[addedElements++] = tempRight[j++];
        }
    }

    while (i < leftSize) {
        islands[addedElements++] = tempLeft[i++];
    }
    while (j < rightSize) {
        islands[addedElements++] = tempRight[j++];
    }
}
