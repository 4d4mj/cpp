#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>

// Global counters for different phases
int g_pair_comparisons = 0;
int g_insertion_comparisons = 0;
int g_remaining_comparisons = 0;

// We'll need to instrument the algorithm - let's test with n=21 sorted input
int main()
{
    std::cout << "Detailed analysis for n=21 (sorted input)\n";
    std::cout << "==========================================\n\n";

    std::vector<int> input;
    for (int i = 1; i <= 21; ++i)
        input.push_back(i);

    std::deque<int> test_deque(input.begin(), input.end());
    PmergeMe::nbr_of_comps = 0;

    PmergeMe pm;
    pm.sort_deque(test_deque);

    std::cout << "\nTotal comparisons: " << PmergeMe::nbr_of_comps << "\n";
    std::cout << "Expected S(21): 66\n";
    std::cout << "Difference: " << (PmergeMe::nbr_of_comps - 66) << "\n\n";

    // Let's manually trace through what should happen for n=21:
    std::cout << "Expected breakdown for Ford-Johnson with n=21:\n";
    std::cout << "----------------------------------------------\n";
    std::cout << "1. Initial pairing (n/2 = 10 comparisons): 10\n";
    std::cout << "2. Recursive sort of maxima (S(10) = 22): 22\n";
    std::cout << "3. Insert b1 (always first, 0 comparisons): 0\n";
    std::cout << "4. Insert pendings via Jacobsthal order:\n";

    // Jacobsthal sequence: 1, 1, 3, 5, 11, 21, ...
    // For n=21 pairs, we have 10 pairs after pairing
    // Main chain starts with 2 elements (winners of first 2 pairs)
    // Pend chain has 8 elements (losers of pairs 3-10) + possibly odd element

    std::cout << "   - J(2)=3: insert b3, b2 (search in 3,2 positions): ~4 comps\n";
    std::cout << "   - J(3)=5: insert b5, b4 (search in 5,4 positions): ~5 comps\n";
    std::cout << "   - J(4)=11: but we only have 9 pends, so we stop\n";
    std::cout << "   - Insert remaining: b9, b8, b7, b6\n";
    std::cout << "\nThe paper claims this should total exactly 66 comparisons.\n";
    std::cout << "\nPossible causes for +1:\n";
    std::cout << "  - Off-by-one in search bounds\n";
    std::cout << "  - Incorrect handling of the straggler element\n";
    std::cout << "  - Wrong Jacobsthal group boundaries\n";

    return 0;
}
