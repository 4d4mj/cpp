#ifndef DEQUE_SORT_HPP
#define DEQUE_SORT_HPP

#include "DequeElement.hpp"
#include <deque>
#include <vector>

// Convert raw integers to DequeElements with index tracking
std::deque<DequeElement> wrapDequeWithIndices(const std::deque<int> &data);

// Extract values from DequeElements back to integers
std::deque<int> unwrapDequeElements(const std::deque<DequeElement> &elements);

// Pair up elements and ensure larger element is first in each pair
// Returns: main chain (larger elements) and pend chain (smaller elements)
void pairAndSortDequeElements(const std::deque<DequeElement> &data,
                               std::deque<DequeElement> &main,
                               std::deque<DequeElement> &pend,
                               int &compCount);

// Reorder pend chain to match the sorted main chain
// After main is sorted recursively, we need to reorder pend to match
std::deque<DequeElement> reorderDequePend(const std::deque<DequeElement> &originalMain,
                                          const std::deque<DequeElement> &sortedMain,
                                          const std::deque<DequeElement> &originalPend);

// Binary search to find insertion position in sorted main chain
// Searches within [0, high] range
// Returns the index where 'pend' should be inserted
int binarySearchDeque(const std::deque<DequeElement> &main,
                      const DequeElement &pend,
                      int high,
                      int &compCount);

// Insert pend elements into main chain using Jacobsthal insertion order
void insertDequePendIntoMain(std::deque<DequeElement> &main,
                             const std::deque<DequeElement> &pend,
                             int &compCount);

// Recursive Ford-Johnson merge-insert sort for deques
std::deque<DequeElement> fordJohnsonSortDequeRecursive(
    const std::deque<DequeElement> &data,
    int &compCount);

// Main entry point for sorting a deque of integers
void fordJohnsonSortDeque(std::deque<int> &deq, int &compCount);

#endif
