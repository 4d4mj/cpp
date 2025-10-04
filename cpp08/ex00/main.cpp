#include <iostream>
#include <vector>
#include "easyfind.hpp"

int main() {
    // Create a vector of integers.
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);

    // Attempt to find the value 30 in the vector.
    try {
        std::vector<int>::iterator it = easyfind(vec, 30);
        std::cout << "Found: " << *it << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Value 30 not found." << std::endl;
    }

    // Attempt to find the value 50 in the vector.
    try {
        std::vector<int>::iterator it = easyfind(vec, 50);
        std::cout << "Found: " << *it << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Value 50 not found." << std::endl;
    }

    return 0;
}
