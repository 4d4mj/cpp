#ifndef PRINT_HELPERS_HPP
#define PRINT_HELPERS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include "Colors.hpp"

// Forward declarations
template <typename T>
bool _comp(T lv, T rv);

long _jacobsthal_number(long n);

extern bool g_verbose;

#define DEBUG_PRINT(x) \
  do                   \
  {                    \
    if (g_verbose)     \
    {                  \
      std::cout << x;  \
    }                  \
  } while (0)

void printOneTime(const std::string &msg);

namespace print_detail
{
void indentLevel(std::size_t level, std::size_t spacesPerLevel = 2);
void indentAdditional(std::size_t spaces);
}

// Determine the maximum width needed for your numbers
template <typename Iterator>
size_t getMaxWidth(const std::vector<Iterator> &mainChain)
{
  size_t maxWidth = 0;
  for (typename std::vector<Iterator>::const_iterator it = mainChain.begin(); it != mainChain.end(); ++it)
  {
    std::ostringstream oss;
    oss << **it;
    maxWidth = std::max(maxWidth, oss.str().size());
  }
  return maxWidth;
}

template <typename Iterator>
bool compareAndPrintPair(Iterator this_pair, Iterator next_pair)
{
  // Do the comparison ONCE and store the result
  bool result = _comp(next_pair, this_pair);

  if (g_verbose)
  {
    print_detail::indentLevel(1);
    if (result)
    {
      std::cout << YELLOW << "⚖️  Compare: " << RESET
                << "[" << GREEN << *this_pair << RESET << " > " << RED << *next_pair << RESET << "] "
                << YELLOW << "→ swap" << RESET << std::endl;
    }
    else
    {
      std::cout << YELLOW << "⚖️  Compare: " << RESET
                << "[" << RED << *this_pair << RESET << " < " << GREEN << *next_pair << RESET << "] "
                << GREEN << "→ keep" << RESET << std::endl;
    }
  }

  return result;
}

#endif // PRINT_HELPERS_HPP
