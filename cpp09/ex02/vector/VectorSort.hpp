#ifndef VECTOR_SORT_HPP
#define VECTOR_SORT_HPP

#include "VectorElement.hpp"
#include <vector>

// Convert raw integers to VectorElements with index tracking
std::vector<VectorElement> wrapVectorWithIndices(const std::vector<int> &data);

// Extract values from VectorElements back to integers
std::vector<int> unwrapVectorElements(const std::vector<VectorElement> &elements);

// Pair up elements and ensure larger element is first in each pair
// Returns: main chain (larger elements) and pend chain (smaller elements)
void pairAndSortVectorElements(const std::vector<VectorElement> &data,
                                std::vector<VectorElement> &main,
                                std::vector<VectorElement> &pend,
                                int &compCount);

// Reorder pend chain to match the sorted main chain
// After main is sorted recursively, we need to reorder pend to match
std::vector<VectorElement> reorderVectorPend(const std::vector<VectorElement> &originalMain,
                                             const std::vector<VectorElement> &sortedMain,
                                             const std::vector<VectorElement> &originalPend);

// Binary search to find insertion position in sorted main chain
// Searches within [0, high] range
// Returns the index where 'pend' should be inserted
int binarySearchVector(const std::vector<VectorElement> &main,
                       const VectorElement &pend,
                       int high,
                       int &compCount);

// Insert pend elements into main chain using Jacobsthal insertion order
void insertVectorPendIntoMain(std::vector<VectorElement> &main,
                              const std::vector<VectorElement> &pend,
                              int &compCount);

// Recursive Ford-Johnson merge-insert sort for vectors
std::vector<VectorElement> fordJohnsonSortVectorRecursive(
    const std::vector<VectorElement> &data,
    int &compCount);

// Main entry point for sorting a vector of integers
void fordJohnsonSortVector(std::vector<int> &vec, int &compCount);

#endif
