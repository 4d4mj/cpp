#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

// Convert container to string for display
template <typename Container>
std::string containerToStr(const Container &container)
{
    std::stringstream ss;
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
    return ss.str();
}

// Print before and after sequences
template <typename Container>
void printBeforeAfter(const Container &before, const Container &after)
{
    std::cout << "Before: " << containerToStr(before) << std::endl;
    std::cout << "After:  " << containerToStr(after) << std::endl;
}

// Print timing information
inline void printTiming(const std::string &containerType, std::size_t size, double timeInSeconds)
{
    double timeInMicroseconds = timeInSeconds * 1000000.0;
    std::cout << "Time to process a range of "
              << size
              << " elements with "
              << containerType << " : "
              << std::fixed << std::setprecision(5)
              << timeInMicroseconds << " us" << std::endl;
}

// Print number of comparisons
inline void printComparisons(int comparisons)
{
    // Comparison count not required by subject
    (void)comparisons;
    return;

    std::cout << "Number of comparisons: " << comparisons << std::endl;
}

#endif // PRINT_HPP
