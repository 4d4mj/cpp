#include <iostream>
#include "Array.hpp" // You could also include "Array.h" if preferred.

int main() {
    // Test 1: Default constructor (empty array)
    Array<int> empty;
    std::cout << "Empty array size: " << empty.size() << std::endl;
    try {
        // This should throw an exception because the array is empty.
        std::cout << "Accessing element in empty array: " << empty[0] << std::endl;
    } catch (std::exception &e) {
        std::cout << "Exception caught: accessing element in an empty array." << std::endl;
    }

    // Test 2: Array of size 5.
    Array<int> arr(5);
    std::cout << "\nArray of ints, size: " << arr.size() << std::endl;
    // Initialize the array.
    for (unsigned int i = 0; i < arr.size(); ++i) {
        arr[i] = i * 10;
    }
    // Display the array.
    for (unsigned int i = 0; i < arr.size(); ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }

    // Test 3: Copy constructor.
    Array<int> copy = arr;
    std::cout << "\nCopy of array:" << std::endl;
    for (unsigned int i = 0; i < copy.size(); ++i) {
        std::cout << "copy[" << i << "] = " << copy[i] << std::endl;
    }
    // Modify the original array.
    arr[0] = 100;
    std::cout << "\nAfter modifying arr[0]:" << std::endl;
    std::cout << "arr[0] = " << arr[0] << std::endl;
    std::cout << "copy[0] = " << copy[0] << " (should be unchanged)" << std::endl;

    // Test 4: Assignment operator.
    Array<int> assign;
    assign = arr;
    std::cout << "\nAssigned array:" << std::endl;
    for (unsigned int i = 0; i < assign.size(); ++i) {
        std::cout << "assign[" << i << "] = " << assign[i] << std::endl;
    }

    // Test 5: Out-of-bounds access.
    try {
        std::cout << "\nAccessing arr[10] (out-of-bounds): " << arr[10] << std::endl;
    } catch (std::exception &e) {
        std::cout << "Exception caught: accessing arr[10] which is out-of-bounds." << std::endl;
    }

    return 0;
}
