#ifndef RESULT_PRINT_HPP
#define RESULT_PRINT_HPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "Colors.hpp"

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

inline void printResultHeader()
{
  std::cout << std::endl;
  std::cout << BOLD << CYAN << "╔═════════════════════════════════════════════════════════════════════════════════╗" << RESET << std::endl;
  std::cout << BOLD << CYAN << "║                               📊 RESULTS                                        ║" << RESET << std::endl;
  std::cout << BOLD << CYAN << "╚═════════════════════════════════════════════════════════════════════════════════╝" << RESET << std::endl;
  std::cout << std::endl;
}

template <typename Container>
void printBeforeAfter(const Container &before, const Container &after)
{
  std::cout << RED << BOLD << "Before: " << RESET << containerToStr(before) << std::endl;
  std::cout << GREEN << BOLD << "After:  " << RESET << containerToStr(after) << std::endl;
  std::cout << std::endl;
}

inline void printTiming(const std::string &containerType, std::size_t size, double timeInSeconds)
{
  std::cout << YELLOW << "⏱️  Time to process a range of " << RESET
            << BOLD << size << RESET
            << YELLOW << " elements with " << RESET
            << CYAN << BOLD << containerType << RESET << ": "
            << std::fixed << std::setprecision(6)
            << timeInSeconds << "s" << std::endl;
}

inline void printComparisons(int comparisons)
{
  std::cout << std::endl;
  std::cout << MAGENTA << BOLD << "🔢 Number of comparisons: " << RESET << comparisons << std::endl;
}

#endif // RESULT_PRINT_HPP
