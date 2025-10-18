#ifndef JACOBSTHAL_HPP
#define JACOBSTHAL_HPP

#include <vector>
#include <cstddef>

// Calculate a single Jacobsthal number J(n)
// Formula: J(n) = J(n-1) + 2*J(n-2), with J(0)=0, J(1)=1
long calculateJacobsthalNumber(long n);

// Generate Jacobsthal numbers starting from J(3) until they exceed size
// Returns: [J(3), J(4), J(5), ...] while J(i) <= size
std::vector<int> generateJacobsthalSequence(std::size_t size);

// Fill indices backward from each Jacobsthal number
// For each jacobNum in sequence, fills [jacobNum, jacobNum-1, ..., prevNum+1]
// Example: if jacobSequence = [5, 11], fills [5,4,3,2] then [11,10,9,8,7,6]
void fillBackwardFromJacobsthal(std::vector<int> &result,
                                 const std::vector<int> &jacobSequence);

// Fill any remaining indices from totalSize down to 1 that weren't filled
void fillRemainingIndices(std::vector<int> &result, std::size_t totalSize);

// Build the complete insertion order using Jacobsthal numbers
// This is the main function that orchestrates the above helpers
std::vector<int> buildInsertionOrder(std::size_t pendSize);

#endif
