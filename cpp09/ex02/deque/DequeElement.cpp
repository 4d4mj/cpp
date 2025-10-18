#include "DequeElement.hpp"

DequeElement::DequeElement() : value(0), index(0) {}

DequeElement::DequeElement(int v, std::size_t idx) : value(v), index(idx) {}

bool compareDequeElements(const DequeElement &lhs, const DequeElement &rhs, int &compCount)
{
    ++compCount;
    if (lhs.value == rhs.value)
        return lhs.index > rhs.index;
    return lhs.value > rhs.value;
}
