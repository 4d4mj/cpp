#include "../PmergeMe.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <sstream>

// Suppress verbose output (external declaration)
// Note: g_verbose is defined in PrintHelpers.cpp

// Structure to hold test statistics
struct TestStats {
    int comparisons;
    std::vector<int> sequence;
    std::string case_type;
};

// Generate a random permutation of numbers from 1 to n
std::vector<int> generate_random_permutation(int n) {
    std::vector<int> result;
    for (int i = 1; i <= n; i++) {
        result.push_back(i);
    }
    std::random_shuffle(result.begin(), result.end());
    return result;
}

// Generate sorted sequence
std::vector<int> generate_sorted(int n) {
    std::vector<int> result;
    for (int i = 1; i <= n; i++) {
        result.push_back(i);
    }
    return result;
}

// Generate reverse sorted sequence
std::vector<int> generate_reverse_sorted(int n) {
    std::vector<int> result;
    for (int i = n; i >= 1; i--) {
        result.push_back(i);
    }
    return result;
}

// Generate alternating high-low pattern
std::vector<int> generate_alternating(int n) {
    std::vector<int> result;
    int low = 1, high = n;
    bool pick_low = true;
    while (low <= high) {
        if (pick_low) {
            result.push_back(low++);
        } else {
            result.push_back(high--);
        }
        pick_low = !pick_low;
    }
    return result;
}

// Generate mostly sorted with a few elements out of place
std::vector<int> generate_mostly_sorted(int n) {
    std::vector<int> result = generate_sorted(n);
    if (n > 4) {
        // Swap a few random pairs
        int swaps = n / 10 + 1;
        for (int i = 0; i < swaps; i++) {
            int idx1 = rand() % n;
            int idx2 = rand() % n;
            std::swap(result[idx1], result[idx2]);
        }
    }
    return result;
}

// Convert vector to string for display
std::string vec_to_string(const std::vector<int>& vec) {
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < vec.size(); i++) {
        if (i > 0) oss << " ";
        oss << vec[i];
    }
    oss << "]";
    return oss.str();
}

// Run a single test and return the number of comparisons
int run_test(std::vector<int> input) {
    PmergeMe pm;
    PmergeMe::nbrOfComparisons = 0;
    pm.sortVector(input);
    return PmergeMe::nbrOfComparisons;
}

void print_histogram(const std::map<int, int>& comp_counts, int total_tests) {
    std::cout << "\n=== HISTOGRAM OF COMPARISONS ===\n";
    
    for (std::map<int, int>::const_iterator it = comp_counts.begin(); 
         it != comp_counts.end(); ++it) {
        int comparisons = it->first;
        int count = it->second;
        double percentage = (count * 100.0) / total_tests;
        
        std::cout << std::setw(4) << comparisons << " comparisons: " 
                  << std::setw(6) << count << " cases (" 
                  << std::setw(5) << std::fixed << std::setprecision(2) << percentage 
                  << "%) ";
        
        // Draw bar
        int bar_length = (count * 50) / total_tests;
        if (bar_length == 0 && count > 0) bar_length = 1;
        for (int i = 0; i < bar_length; i++) {
            std::cout << "█";
        }
        std::cout << "\n";
    }
}

void print_outliers(const std::vector<TestStats>& all_tests, int expected_comps, int /* n */) {
    std::vector<TestStats> outliers;
    
    for (size_t i = 0; i < all_tests.size(); i++) {
        if (all_tests[i].comparisons != expected_comps) {
            outliers.push_back(all_tests[i]);
        }
    }
    
    if (outliers.empty()) {
        std::cout << "\n✓ All tests used exactly " << expected_comps << " comparisons!\n";
        return;
    }
    
    std::cout << "\n=== OUTLIERS (not " << expected_comps << " comparisons) ===\n";
    std::cout << "Found " << outliers.size() << " outliers:\n\n";
    
    // Limit display to first 20 outliers if there are many
    size_t display_limit = (outliers.size() > 20) ? 20 : outliers.size();
    
    for (size_t i = 0; i < display_limit; i++) {
        std::cout << "Case " << (i + 1) << " [" << outliers[i].case_type << "]: " 
                  << outliers[i].comparisons << " comparisons\n";
        std::cout << "  Sequence: " << vec_to_string(outliers[i].sequence) << "\n\n";
    }
    
    if (outliers.size() > display_limit) {
        std::cout << "... and " << (outliers.size() - display_limit) << " more outliers\n";
    }
}

int main(int argc, char** argv) {
    if (argc < 2 || argc > 4) {
        std::cout << "Usage: " << argv[0] << " <n> [num_random_cases] [expected_comparisons]\n";
        std::cout << "  n: number of elements to sort\n";
        std::cout << "  num_random_cases: number of random test cases (default: 1000)\n";
        std::cout << "  expected_comparisons: expected number of comparisons (default: calculated)\n";
        std::cout << "\nExample: " << argv[0] << " 21 5000 66\n";
        return 1;
    }
    
    int n = atoi(argv[1]);
    int num_random_cases = (argc >= 3) ? atoi(argv[2]) : 1000;
    int expected_comps = (argc >= 4) ? atoi(argv[3]) : -1;
    
    if (n <= 0) {
        std::cerr << "Error: n must be positive\n";
        return 1;
    }
    
    if (num_random_cases <= 0) {
        std::cerr << "Error: num_random_cases must be positive\n";
        return 1;
    }
    
    srand(time(NULL));
    
    std::cout << "=== FORD-JOHNSON MERGE-INSERTION SORT COMPARISON TESTER ===\n";
    std::cout << "Testing with n = " << n << " elements\n";
    std::cout << "Random test cases: " << num_random_cases << "\n";
    if (expected_comps > 0) {
        std::cout << "Expected comparisons: " << expected_comps << "\n";
    }
    std::cout << "\n";
    
    std::map<int, int> comp_counts; // Map of comparisons -> count
    std::vector<TestStats> all_tests;
    
    // Test 1: Already sorted
    std::cout << "Testing edge cases...\n";
    {
        std::vector<int> test = generate_sorted(n);
        int comps = run_test(test);
        comp_counts[comps]++;
        TestStats stats = {comps, test, "sorted"};
        all_tests.push_back(stats);
        std::cout << "  ✓ Sorted sequence: " << comps << " comparisons\n";
    }
    
    // Test 2: Reverse sorted
    {
        std::vector<int> test = generate_reverse_sorted(n);
        int comps = run_test(test);
        comp_counts[comps]++;
        TestStats stats = {comps, test, "reverse_sorted"};
        all_tests.push_back(stats);
        std::cout << "  ✓ Reverse sorted sequence: " << comps << " comparisons\n";
    }
    
    // Test 3: Alternating
    {
        std::vector<int> test = generate_alternating(n);
        int comps = run_test(test);
        comp_counts[comps]++;
        TestStats stats = {comps, test, "alternating"};
        all_tests.push_back(stats);
        std::cout << "  ✓ Alternating sequence: " << comps << " comparisons\n";
    }
    
    // Test 4-8: Mostly sorted with different random seeds
    for (int i = 0; i < 5; i++) {
        std::vector<int> test = generate_mostly_sorted(n);
        int comps = run_test(test);
        comp_counts[comps]++;
        TestStats stats = {comps, test, "mostly_sorted"};
        all_tests.push_back(stats);
    }
    std::cout << "  ✓ 5 mostly sorted sequences\n";
    
    // Random tests
    std::cout << "\nTesting " << num_random_cases << " random permutations...\n";
    for (int i = 0; i < num_random_cases; i++) {
        std::vector<int> test = generate_random_permutation(n);
        int comps = run_test(test);
        comp_counts[comps]++;
        TestStats stats = {comps, test, "random"};
        all_tests.push_back(stats);
        
        if ((i + 1) % (num_random_cases / 10) == 0) {
            std::cout << "  Progress: " << (i + 1) << "/" << num_random_cases << "\n";
        }
    }
    
    std::cout << "\n=== RESULTS ===\n";
    std::cout << "Total tests: " << all_tests.size() << "\n";
    
    // Find min and max comparisons
    int min_comps = comp_counts.begin()->first;
    int max_comps = comp_counts.rbegin()->first;
    
    std::cout << "Min comparisons: " << min_comps << "\n";
    std::cout << "Max comparisons: " << max_comps << "\n";
    std::cout << "Range: " << (max_comps - min_comps) << "\n";
    
    // Calculate most common
    int most_common_comps = 0;
    int most_common_count = 0;
    for (std::map<int, int>::iterator it = comp_counts.begin(); 
         it != comp_counts.end(); ++it) {
        if (it->second > most_common_count) {
            most_common_count = it->second;
            most_common_comps = it->first;
        }
    }
    
    std::cout << "Most common: " << most_common_comps << " comparisons (" 
              << most_common_count << " cases, " 
              << std::fixed << std::setprecision(2) 
              << (most_common_count * 100.0 / all_tests.size()) << "%)\n";
    
    // Print histogram
    print_histogram(comp_counts, all_tests.size());
    
    // If expected comparisons provided, show outliers
    if (expected_comps > 0) {
        print_outliers(all_tests, expected_comps, n);
        
        int matching = 0;
        for (size_t i = 0; i < all_tests.size(); i++) {
            if (all_tests[i].comparisons == expected_comps) {
                matching++;
            }
        }
        std::cout << "\n=== SUMMARY ===\n";
        std::cout << "Cases with exactly " << expected_comps << " comparisons: " 
                  << matching << "/" << all_tests.size() << " ("
                  << std::fixed << std::setprecision(2)
                  << (matching * 100.0 / all_tests.size()) << "%)\n";
        std::cout << "Cases NOT matching: " << (all_tests.size() - matching) 
                  << " (" << ((all_tests.size() - matching) * 100.0 / all_tests.size()) 
                  << "%)\n";
    }
    
    return 0;
}
