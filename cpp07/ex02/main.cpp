#include <iostream>
#include "Array.hpp"

int main() {
    Array<int> empty;
    std::cout << "Empty array size: " << empty.size() << std::endl;
    try {
        std::cout << "Accessing element in empty array: " << empty[0] << std::endl;
    } catch (std::exception &e) {
        std::cout << "Exception caught: accessing element in an empty array." << std::endl;
    }

    Array<int> arr(5);
    std::cout << "\nArray of ints, size: " << arr.size() << std::endl;
    for (unsigned int i = 0; i < arr.size(); ++i) {
        arr[i] = i * 10;
    }
    for (unsigned int i = 0; i < arr.size(); ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }

    Array<int> copy = arr;
    std::cout << "\nCopy of array:" << std::endl;
    for (unsigned int i = 0; i < copy.size(); ++i) {
        std::cout << "copy[" << i << "] = " << copy[i] << std::endl;
    }
    arr[0] = 100;
    std::cout << "\nAfter modifying arr[0]:" << std::endl;
    std::cout << "arr[0] = " << arr[0] << std::endl;
    std::cout << "copy[0] = " << copy[0] << " (should be unchanged)" << std::endl;

    Array<int> assign;
    assign = arr;
    std::cout << "\nAssigned array:" << std::endl;
    for (unsigned int i = 0; i < assign.size(); ++i) {
        std::cout << "assign[" << i << "] = " << assign[i] << std::endl;
    }

    try {
        std::cout << "\nAccessing arr[10] (out-of-bounds): " << arr[10] << std::endl;
    } catch (std::exception &e) {
        std::cout << "Exception caught: accessing arr[10] which is out-of-bounds." << std::endl;
    }

    return 0;
}
