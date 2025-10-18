#ifndef VECTOR_ELEMENT_HPP
#define VECTOR_ELEMENT_HPP

#include <cstddef>

// Element wrapper for vector values
// Stores both the actual value and its original index for stable sorting
struct VectorElement
{
    int value;
    std::size_t index;

    VectorElement();
    VectorElement(int v, std::size_t idx);
};

// Compare two VectorElements (greater-than comparison)
// Returns true if lhs > rhs
// For equal values, compares by index for stability
bool compareVectorElements(const VectorElement &lhs, const VectorElement &rhs, int &compCount);

#endif
