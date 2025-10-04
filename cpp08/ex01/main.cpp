#include "Span.hpp"
#include <iostream>
#include <vector>

int main() {
    try {
        // Example from the exercise instructions.
        Span sp(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        std::cout << sp.shortestSpan() << std::endl;  // Expected output: 2
        std::cout << sp.longestSpan() << std::endl;   // Expected output: 14

        // Additional test using the range insertion method.
        std::vector<int> moreNumbers;
        for (int i = 0; i < 10000; ++i)
            moreNumbers.push_back(i * 2);  // or any large dataset

        Span spLarge(10000);
        spLarge.addNumbers(moreNumbers.begin(), moreNumbers.end());
        std::cout << "Shortest span in spLarge: " << spLarge.shortestSpan() << std::endl;
        std::cout << "Longest span in spLarge: " << spLarge.longestSpan() << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
