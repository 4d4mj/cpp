#include "Span.hpp"
#include <limits>
#include <stdexcept>

Span::Span(unsigned int N) : _maxSize(N) {}

Span::Span(const Span &other) : _numbers(other._numbers), _maxSize(other._maxSize) {}

Span& Span::operator=(const Span &other) {
    if (this != &other) {
        _numbers = other._numbers;
        _maxSize = other._maxSize;
    }
    return *this;
}

Span::~Span() {}

void Span::addNumber(int num) {
    if (_numbers.size() >= _maxSize)
        throw std::runtime_error("Span is full");
    _numbers.push_back(num);
}

int Span::shortestSpan() const {
    if (_numbers.size() < 2)
        throw std::runtime_error("Not enough numbers to find a span");

    // Copy and sort the numbers.
    std::vector<int> tmp = _numbers;
    std::sort(tmp.begin(), tmp.end());

    // Initialize minSpan with the first adjacent difference.
    int minSpan = std::abs(tmp[1] - tmp[0]);
    for (size_t i = 1; i < tmp.size() - 1; i++) {
        int span = std::abs(tmp[i + 1] - tmp[i]);
        if (span < minSpan)
            minSpan = span;
    }
    return minSpan;
}

int Span::longestSpan() const {
    if (_numbers.size() < 2)
        throw std::runtime_error("Not enough numbers to find a span");

    int minVal = *std::min_element(_numbers.begin(), _numbers.end());
    int maxVal = *std::max_element(_numbers.begin(), _numbers.end());
    return maxVal - minVal;
}
