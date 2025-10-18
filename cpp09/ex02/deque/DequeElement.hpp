#ifndef DEQUE_ELEMENT_HPP
#define DEQUE_ELEMENT_HPP

#include <cstddef>

// Element wrapper for deque values
// Stores both the actual value and its original index for stable sorting
struct DequeElement
{
    int value;
    std::size_t index;

    DequeElement();
    DequeElement(int v, std::size_t idx);
};

// Compare two DequeElements (greater-than comparison)
// Returns true if lhs > rhs
// For equal values, compares by index for stability
bool compareDequeElements(const DequeElement &lhs, const DequeElement &rhs, int &compCount);

#endif
