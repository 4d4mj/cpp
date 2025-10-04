#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <exception>
#include <iterator>

class Span {
public:
    // Constructor: the parameter N is the maximum number of integers allowed.
    Span(unsigned int N);
    Span(const Span &other);
    Span& operator=(const Span &other);
    ~Span();

    // Add a single number; throw an exception if capacity is exceeded.
    void addNumber(int num);

    // Templated function to add a range of numbers.
    template <typename Iterator>
    void addNumbers(Iterator begin, Iterator end) {
        // Check if there is enough space for all new elements.
        if (std::distance(begin, end) + _numbers.size() > _maxSize)
            throw std::runtime_error("Not enough space to add all numbers.");
        _numbers.insert(_numbers.end(), begin, end);
    }

    // Compute the smallest difference between any two numbers.
    int shortestSpan() const;

    // Compute the largest difference (between the minimum and maximum).
    int longestSpan() const;

private:
    std::vector<int> _numbers;
    unsigned int _maxSize;
};

#endif // SPAN_HPP
