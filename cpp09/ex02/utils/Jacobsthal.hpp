#ifndef JACOBSTHAL_HPP
#define JACOBSTHAL_HPP

#include <vector>
#include <cstddef>

// Calculate a single Jacobsthal number J(n)
long calculateJacobsthalNumber(long n);

// Generate Jacobsthal numbers starting from J(3) until they exceed size
// Returns: [J(3), J(4), J(5), ...] while J(i) <= size
std::vector<int> generateJacobsthalSequence(std::size_t size);

// Fill indices backward from each Jacobsthal number
// For each jacobNum in sequence, fills [jacobNum, jacobNum-1, ..., prevNum+1]
void fillBackwardFromJacobsthal(std::vector<int> &result,
                                 const std::vector<int> &jacobSequence);

// Fill any remaining indices from totalSize down to 1 that weren't filled
void fillRemainingIndices(std::vector<int> &result, std::size_t totalSize);

// Build the complete insertion order using Jacobsthal numbers
std::vector<int> buildInsertionOrder(std::size_t pendSize);

#endif
