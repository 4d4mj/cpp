#include "PmergeMe.hpp"
#include "print/Print.hpp"
#include "utils/InputParser.hpp"
#include "utils/Validator.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char **argv)
{
    PmergeMe pm;

    // Validate input arguments
    std::string status = validateArgs(argc, argv);
    if (status != "")
    {
        std::cerr << "Error: " << status << "\n";
        return EXIT_FAILURE;
    }

    // Store original data for display and validation
    std::vector<int> originalVec = argvToVector(argc, argv);

    // Sort with vector
    clock_t startVec = clock();
    std::vector<int> vec = argvToVector(argc, argv);
    pm.sortVector(vec);
    clock_t endVec = clock();
    double timeElapsedVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC;

    // Sort with deque
    PmergeMe::nbrOfComparisons = 0;
    clock_t startDeque = clock();
    std::deque<int> deque = argvToDeque(argc, argv);
    pm.sortDeque(deque);
    clock_t endDeque = clock();
    double timeElapsedDeque = static_cast<double>(endDeque - startDeque) / CLOCKS_PER_SEC;

    // Validate vector sorting
    if (!isSorted(vec) || (int)vec.size() != (argc - 1) || !retainedOriginalValues(originalVec, vec))
    {
        std::cout << "Vector was not sorted properly.\n";
        return 1;
    }

    // Validate deque sorting
    if (!isSorted(deque) || (int)deque.size() != (argc - 1))
    {
        std::cout << "Deque was not sorted properly.\n";
        return 1;
    }

    // Display results
    printResultHeader();
    printBeforeAfter(originalVec, vec);
    printTiming("std::vector", vec.size(), timeElapsedVec);
    printTiming("std::deque", deque.size(), timeElapsedDeque);
    printComparisons(PmergeMe::nbrOfComparisons);
}
