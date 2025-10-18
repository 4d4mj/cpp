#include <iostream>
#include <string>
#include "iter.hpp"

template <typename T>
void printElement(const T &element) {
    std::cout << element << " ";
}

int main() {
    int arrInt[] = {1, 2, 3, 4, 5};
    size_t arrIntSize = sizeof(arrInt) / sizeof(arrInt[0]);
    std::cout << "Array of ints: ";
    iter(arrInt, arrIntSize, printElement<int>);
    std::cout << std::endl;

    std::string arrStr[] = {"Hello", "World", "Templates"};
    size_t arrStrSize = sizeof(arrStr) / sizeof(arrStr[0]);
    std::cout << "Array of strings: ";
    iter(arrStr, arrStrSize, printElement<std::string>);
    std::cout << std::endl;

    double arrDouble[] = {3.14, 2.718, 1.618};
    size_t arrDoubleSize = sizeof(arrDouble) / sizeof(arrDouble[0]);
    std::cout << "Array of doubles: ";
    iter(arrDouble, arrDoubleSize, printElement<double>);
    std::cout << std::endl;

    return 0;
}
