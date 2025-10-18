#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

// ANSI color codes
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"

// Convert container to string for display
template <typename Container>
std::string containerToStr(const Container &container)
{
    std::stringstream ss;
    ss << "[";
    if (!container.empty())
    {
        typename Container::const_iterator it = container.begin();
        ss << *it;
        ++it;
        for (; it != container.end(); ++it)
        {
            ss << " " << *it;
        }
    }
    ss << "]";
    return ss.str();
}

// Print result header
inline void printResultHeader()
{
    std::cout << std::endl;
    std::cout << BOLD << CYAN << "╔═════════════════════════════════════════════════════════════════════════════════╗" << RESET << std::endl;
    std::cout << BOLD << CYAN << "║                               📊 RESULTS                                        ║" << RESET << std::endl;
    std::cout << BOLD << CYAN << "╚═════════════════════════════════════════════════════════════════════════════════╝" << RESET << std::endl;
    std::cout << std::endl;
}

// Print before and after sequences
template <typename Container>
void printBeforeAfter(const Container &before, const Container &after)
{
    std::cout << RED << BOLD << "Before: " << RESET << containerToStr(before) << std::endl;
    std::cout << GREEN << BOLD << "After:  " << RESET << containerToStr(after) << std::endl;
    std::cout << std::endl;
}

// Print timing information
inline void printTiming(const std::string &containerType, std::size_t size, double timeInSeconds)
{
    std::cout << YELLOW << "⏱️  Time to process a range of " << RESET
              << BOLD << size << RESET
              << YELLOW << " elements with " << RESET
              << CYAN << BOLD << containerType << RESET << ": "
              << std::fixed << std::setprecision(6)
              << timeInSeconds << "s" << std::endl;
}

// Print number of comparisons
inline void printComparisons(int comparisons)
{
    std::cout << std::endl;
    std::cout << MAGENTA << BOLD << "🔢 Number of comparisons: " << RESET << comparisons << std::endl;
}

#endif // PRINT_HPP
