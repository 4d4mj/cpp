#include "VectorElement.hpp"

VectorElement::VectorElement() : value(0), index(0) {}

VectorElement::VectorElement(int v, std::size_t idx) : value(v), index(idx) {}

bool compareVectorElements(const VectorElement &lhs, const VectorElement &rhs, int &compCount)
{
    ++compCount;
    if (lhs.value == rhs.value)
        return lhs.index > rhs.index;
    return lhs.value > rhs.value;
}
