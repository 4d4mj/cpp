#include <iostream>
#include <string>
#include "iter.hpp"

// A function template that prints an element.
// Note: We take the element by const reference to work with any type.
template <typename T>
void printElement(const T &element) {
    std::cout << element << " ";
}

int main() {
    // Test with an array of ints
    int arrInt[] = {1, 2, 3, 4, 5};
    size_t arrIntSize = sizeof(arrInt) / sizeof(arrInt[0]);
    std::cout << "Array of ints: ";
    // Pass an instantiated function template (printElement<int>)
    iter(arrInt, arrIntSize, printElement<int>);
    std::cout << std::endl;

    // Test with an array of std::string
    std::string arrStr[] = {"Hello", "World", "Templates"};
    size_t arrStrSize = sizeof(arrStr) / sizeof(arrStr[0]);
    std::cout << "Array of strings: ";
    iter(arrStr, arrStrSize, printElement<std::string>);
    std::cout << std::endl;

    // Test with an array of doubles
    double arrDouble[] = {3.14, 2.718, 1.618};
    size_t arrDoubleSize = sizeof(arrDouble) / sizeof(arrDouble[0]);
    std::cout << "Array of doubles: ";
    iter(arrDouble, arrDoubleSize, printElement<double>);
    std::cout << std::endl;

    return 0;
}
