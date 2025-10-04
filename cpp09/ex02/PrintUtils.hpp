#ifndef PRINT_UTILS_HPP
#define PRINT_UTILS_HPP

#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

// Do not include "PmergeMe.hpp" here to break the circular dependency.
// Instead, forward-declare _comp so we can use it in compareAndPrintPair:
template <typename T>
bool _comp(T lv, T rv);

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

template <typename Container>
void printContainerAsGroups(const Container &container, int groupSize, bool useColor = true)
{
  if (!g_verbose)
    return;

  typedef typename Container::const_iterator Iterator;
  static bool firstSorted = false;
  Iterator it = container.begin();

  int totalGroups = container.size() / groupSize;
  int groupIndex = 0;
  bool isTwo = totalGroups <= 2;
  bool isOdd = totalGroups % 2 == 1;

  if (isTwo)
  {
    firstSorted = true;
  }

  std::cout << std::endl
            << std::endl;

  while (it != container.end())
  {
    int available = std::distance(it, container.end());
    bool incomplete = (available < groupSize);
    bool isFirst = groupIndex == 0;
    bool isLast = groupIndex == totalGroups - 1;
    bool discarded = incomplete || (isLast && isOdd);

    std::string groupColor = useColor ? ((firstSorted && isFirst) || (groupIndex % 2 == 1) ? GREEN : RED) : "";

    std::cout << (incomplete ? RED : discarded ? MAGENTA
                                               : "")
              << "[" << RESET;
    for (int j = 0; j < groupSize; j++)
    {
      bool isLastElement = j == groupSize - 1;
      std::string color = isLastElement ? groupColor : "";

      if (it == container.end())
        break;
      std::cout << (incomplete ? RED : discarded ? MAGENTA
                                                 : color)
                << *it << RESET;
      ++it;
      if (j < groupSize - 1 && it != container.end())
        std::cout << (incomplete ? RED : discarded ? MAGENTA
                                                   : "")
                  << ", ";
    }
    std::cout << (incomplete ? RED : discarded ? MAGENTA
                                               : "")
              << "]" << RESET << " ";
    groupIndex++;
  }
  std::cout << std::endl
            << std::endl;
}

template <typename Container>
void printRecursionLevel(int pair_units_nbr, bool is_odd, const Container &container, int pair_level, bool useColor, bool insertion = false)
{
  if (!g_verbose)
    return;

  int recursion_level = 0;
  int temp = pair_level;

  if (!g_verbose)
    return;

  while (temp > 1)
  {
    recursion_level++;
    temp /= 2;
  }
  if (insertion)
    printOneTime("================================================ Insertion Phase =================================================");
  DEBUG_PRINT(std::endl
              << "======================================== Recursion Level " << recursion_level + 1
              << " (Pair Level " << pair_level << ") ======================================== " << std::endl);

  DEBUG_PRINT(pair_units_nbr << " elements before sorting"
                             << (is_odd ? " (odd)" : " (even)"));

  printContainerAsGroups(container, pair_level, useColor);
}

template <typename Iterator>
bool compareAndPrintPair(Iterator this_pair, Iterator next_pair)
{

  if (g_verbose)
  {
    if (_comp(next_pair, this_pair))
    {
      DEBUG_PRINT("[" << GREEN << *this_pair << RESET << " > " << RED << *next_pair << RESET << "] ");
      return true;
    }
    else
    {
      DEBUG_PRINT("[" << RED << *this_pair << RESET << " < " << GREEN << *next_pair << RESET << "] ");
      return false;
    }
  }
  else
    return _comp(next_pair, this_pair);
}

template <typename Iterator>
void printChains(const std::vector<Iterator> &mainChain, const std::vector<Iterator> &pendChain, bool onlyMain = false, bool onlyPend = false, bool useLabels = false)
{
  if (!g_verbose)
    return;

  int available = mainChain.size();
  if (!onlyPend)
  {
    if (useLabels)
      DEBUG_PRINT("Main:" << std::endl);
    std::cout << "[";
    for (typename std::vector<Iterator>::const_iterator it = mainChain.begin(); it != mainChain.end(); ++it)
    {
      bool incomplete = (--available == 0);
      std::cout << GREEN << **it << RESET;
      std::cout << (incomplete ? "" : ", ");
    }
    std::cout << "]" << std::endl
              << std::endl;
  }

  if (onlyMain)
    return;

  available = pendChain.size();
  if (useLabels)
    DEBUG_PRINT("Pend:" << std::endl);
  std::cout << "[";
  for (typename std::vector<Iterator>::const_iterator it = pendChain.begin(); it != pendChain.end(); ++it)
  {
    bool incomplete = (--available == 0);
    std::cout << RED << **it << RESET;
    std::cout << (incomplete ? "" : ", ");
  }
  std::cout << "]" << std::endl
            << std::endl;
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
void printInsertionVisual(const std::vector<Iterator> &mainChain, typename std::vector<Iterator>::const_iterator idx)
{
  if (!g_verbose)
    return;

  size_t maxWidth = getMaxWidth(mainChain);
  // Calculate total fixed-width for each element including a comma and space if needed.
  // Adjust spacing if you have different delimiters.
  size_t elementWidth = maxWidth + 2;

  // Determine the insertion index in terms of fixed width units
  size_t insertion_index = std::distance(mainChain.begin(), idx) * elementWidth;
  for (size_t i = 0; i < insertion_index; ++i)
    std::cout << " "; // adjust spacing as needed
  std::cout << YELLOW << "|" << RESET << std::endl;

  std::cout << CYAN << "[";
  int available = mainChain.size();
  for (typename std::vector<Iterator>::const_iterator it = mainChain.begin(); it != mainChain.end(); ++it)
  {
    bool incomplete = (--available == 0);
    // Print the number in a fixed-width field.
    std::cout << std::setw(maxWidth) << **it;
    std::cout << (incomplete ? "" : ", ");
  }
  std::cout << "]" << RESET
            << std::endl;
}

template <typename Iterator>
void printRemainingInsertion(const std::vector<Iterator> &mainChain, const Iterator &currPend, size_t insertionIndex)
{
  if (!g_verbose)
    return;
  // Note: currPend is now expected to be the element (Iterator) stored in the vector.
  DEBUG_PRINT("Inserting remaining pend value " << *(currPend)
                                                << " into main chain at position " << insertionIndex << std::endl);
  DEBUG_PRINT("After remaining insertion loop, main chain:" << std::endl);

  typedef typename std::vector<Iterator>::const_iterator const_iter;
  for (const_iter it = mainChain.begin(); it != mainChain.end(); ++it)
    std::cout << *(*it) << " "; // Dereference once: *it gives the Iterator, then * gives the value.
  std::cout << std::endl;
}

template <typename Iterator>
void printJacobsthalInfo(int k, int curr_jacobsthal, int jacobsthal_diff, const std::vector<Iterator> &main, const std::vector<Iterator> &pend)
{
  DEBUG_PRINT("Jacobsthal number for k = " << k
                                           << " is " << curr_jacobsthal
                                           << std::endl);

  printChains(main, pend, false, true);
  
  DEBUG_PRINT("diff = j(" << k << ") - j(" << k - 1 << ") = ["
                   << YELLOW << jacobsthal_diff
                   << RESET
                   << "], means "
                   << YELLOW
                   << jacobsthal_diff
                   << " insertions"
                   << RESET
                   << std::endl
                   << std::endl);
}

#endif // PRINT_UTILS_HPP
