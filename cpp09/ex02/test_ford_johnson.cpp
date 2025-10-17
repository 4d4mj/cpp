#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
#include <iomanip>

// Theoretical Ford-Johnson comparison bounds
// Based on the paper: S(n) = optimal comparison count for n elements
int theoretical_S(int n)
{
    if (n <= 1) return 0;
    if (n == 2) return 1;

    // Exact values from OEIS A036604: optimal comparison count for sorting n elements
    // These are proven optimal for n <= 22
    int exact_values[] = {
        0,   // n=0 (placeholder)
        0,   // n=1
        1,   // n=2
        3,   // n=3
        5,   // n=4
        7,   // n=5
        10,  // n=6
        13,  // n=7
        16,  // n=8
        19,  // n=9
        22,  // n=10
        26,  // n=11
        30,  // n=12
        34,  // n=13
        38,  // n=14
        42,  // n=15
        46,  // n=16
        50,  // n=17
        54,  // n=18
        58,  // n=19
        62,  // n=20
        66,  // n=21
        71   // n=22
    };

    if (n < static_cast<int>(sizeof(exact_values) / sizeof(exact_values[0])))
        return exact_values[n];

    // For larger n, use approximation: n*log₂(n) - 2^(log₂(n)) + 1
    return static_cast<int>(n * log2(n) - pow(2, floor(log2(n))) + 1);
}

void test_sequence(const std::vector<int>& input, const std::string& description)
{
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "Test: " << description << "\n";
    std::cout << "Input size: " << input.size() << "\n";
    std::cout << "Input: ";
    for (size_t i = 0; i < input.size() && i < 21; ++i)
        std::cout << input[i] << " ";
    if (input.size() > 21) std::cout << "...";
    std::cout << "\n";

    // Test with deque
    std::deque<int> test_deque(input.begin(), input.end());
    PmergeMe::nbr_of_comps = 0;

    PmergeMe pm;
    pm.sort_deque(test_deque);

    int actual = PmergeMe::nbr_of_comps;
    int theoretical = theoretical_S(input.size());
    int diff = actual - theoretical;

    std::cout << "Comparisons: " << actual << "\n";
    std::cout << "Theoretical S(" << input.size() << "): " << theoretical << "\n";
    std::cout << "Difference: " << (diff >= 0 ? "+" : "") << diff;

    if (diff == 0)
        std::cout << " ✓ OPTIMAL\n";
    else if (diff > 0)
        std::cout << " ✗ TOO MANY\n";
    else
        std::cout << " ✗ ERROR (impossible)\n";

    // Verify sorted
    bool is_sorted = true;
    for (size_t i = 1; i < test_deque.size(); ++i)
    {
        if (test_deque[i-1] > test_deque[i])
        {
            is_sorted = false;
            break;
        }
    }
    std::cout << "Sorted correctly: " << (is_sorted ? "YES" : "NO") << "\n";
}

int main()
{
    std::cout << "Ford-Johnson Merge-Insertion Sort - Comparison Count Verification\n";
    std::cout << "Based on: Ford & Johnson (1959) - Optimal comparison bounds\n";

    // Test 1: n=21 (the example from the paper)
    std::vector<int> test21;
    for (int i = 21; i >= 1; --i) test21.push_back(i);
    test_sequence(test21, "Reverse sorted (n=21) - Should be 66");

    // Test 2: Already sorted
    std::vector<int> sorted21;
    for (int i = 1; i <= 21; ++i) sorted21.push_back(i);
    test_sequence(sorted21, "Already sorted (n=21) - Should be 66");

    // Test 3: Random shuffle
    std::vector<int> shuffle21;
    int arr[] = {15, 7, 21, 3, 18, 9, 12, 6, 20, 1, 14, 11, 8, 19, 4, 17, 2, 13, 10, 5, 16};
    for (int i = 0; i < 21; ++i) shuffle21.push_back(arr[i]);
    test_sequence(shuffle21, "Random shuffle (n=21) - Should be 66");

    // Test smaller sizes
    for (int n = 2; n <= 12; ++n)
    {
        std::vector<int> test_n;
        for (int i = n; i >= 1; --i) test_n.push_back(i);
        test_sequence(test_n, "Reverse sorted (n=" + std::to_string(n) + ")");
    }

    // Print Jacobsthal numbers for reference
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "Jacobsthal numbers (for insertion order):\n";
    for (int k = 0; k <= 10; ++k)
    {
        std::cout << "J(" << k << ") = " << _jacobsthal_number(k) << "\n";
    }

    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "Theoretical S(n) values:\n";
    std::cout << std::setw(4) << "n" << " | " << std::setw(8) << "S(n)" << " | " << "log₂(n!)\n";
    std::cout << std::string(30, '-') << "\n";

    double log_factorial = 0;
    for (int n = 1; n <= 21; ++n)
    {
        log_factorial += log2(n);
        int s_n = theoretical_S(n);
        std::cout << std::setw(4) << n << " | "
                  << std::setw(8) << s_n << " | "
                  << std::fixed << std::setprecision(2) << log_factorial << "\n";
    }

    return 0;
}
