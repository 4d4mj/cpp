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
    std::cout << "   [";
    for (typename std::vector<Iterator>::const_iterator it = mainChain.begin(); it != mainChain.end(); ++it)
    {
      bool incomplete = (--available == 0);
      std::cout << GREEN << **it << RESET;
      std::cout << (incomplete ? "" : ", ");
    }
    std::cout << "]" << std::endl;
  }

  if (onlyMain)
    return;

  available = pendChain.size();
  if (useLabels)
    DEBUG_PRINT("Pend:" << std::endl);
  std::cout << "   [";
  for (typename std::vector<Iterator>::const_iterator it = pendChain.begin(); it != pendChain.end(); ++it)
  {
    bool incomplete = (--available == 0);
    std::cout << RED << **it << RESET;
    std::cout << (incomplete ? "" : ", ");
  }
  std::cout << "]" << std::endl;
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
void printInsertionVisual(const std::vector<Iterator> &mainChain, typename std::vector<Iterator>::const_iterator idx, typename std::vector<Iterator>::const_iterator searchBound)
{
  if (!g_verbose)
    return;

  size_t maxWidth = getMaxWidth(mainChain);
  size_t elementWidth = maxWidth + 2;

  // Show the search space (searchBound is one past the last element to search)
  size_t searchBoundIdx = std::distance(mainChain.begin(), searchBound);
  std::cout << "  " << BLUE << "🔍 Search space: " << RESET << "Main[0.." << (searchBoundIdx > 0 ? searchBoundIdx - 1 : 0) << "] = [";
  for (size_t i = 0; i < searchBoundIdx && i < mainChain.size(); ++i)
  {
    typename std::vector<Iterator>::const_iterator temp = mainChain.begin();
    std::advance(temp, i);
    std::cout << **temp;
    if (i < searchBoundIdx - 1)
      std::cout << ", ";
  }
  std::cout << "]" << std::endl;

  // Print position markers above the array showing search bound
  // Account for opening bracket "["
  std::cout << "  ";  // 2 spaces for "  " before bracket, 1 for "["
  for (size_t i = 0; i < mainChain.size(); ++i)
  {
    if (i == searchBoundIdx)
      std::cout << std::setw(maxWidth) << RED << "|" << RESET;
    else
      std::cout << std::setw(maxWidth) << " ";
    if (i < mainChain.size() - 1)
      std::cout << "  ";
  }
  std::cout << std::endl;

  std::cout << "   ";
  for (size_t i = 0; i < mainChain.size(); ++i)
  {
    if (i < searchBoundIdx)
      std::cout << GREEN << std::setw(elementWidth) << "✓" << RESET;
    else
      std::cout << RED << std::setw(elementWidth) << "✗" << RESET;
    if (i < mainChain.size() - 1)
      std::cout << "  ";
  }
  std::cout << std::endl;

  // Show insertion point
  size_t insertion_index = std::distance(mainChain.begin(), idx) * elementWidth;
  std::cout << "  ";
  for (size_t i = 0; i < insertion_index; ++i)
    std::cout << " ";
  std::cout << YELLOW << "↓ insert here" << RESET << std::endl;

  std::cout << "  " << CYAN << "[";
  int available = mainChain.size();
  for (typename std::vector<Iterator>::const_iterator it = mainChain.begin(); it != mainChain.end(); ++it)
  {
    bool incomplete = (--available == 0);
    std::cout << std::setw(maxWidth) << **it;
    std::cout << (incomplete ? "" : ", ");
  }
  std::cout << "]" << RESET << std::endl << std::endl;
}

template <typename Iterator>
void printRemainingInsertion(const std::vector<Iterator> &mainChain, const Iterator &currPend, size_t insertionIndex, size_t searchBoundIdx, size_t pendIdx, size_t remainingPendSize, bool isOdd)
{
  if (!g_verbose)
    return;

  std::cout << CYAN << "\n╔═════════════════════════════════════════════════════════════════════════════════╗" << RESET << std::endl;
  std::cout << CYAN << "║ " << RESET << YELLOW << BOLD << "Inserting Leftover Elements" << RESET << CYAN << "                                                  ║" << RESET << std::endl;
  std::cout << CYAN << "╚═════════════════════════════════════════════════════════════════════════════════╝" << RESET << std::endl;

  std::cout << MAGENTA << "→ Inserting remaining pend[" << pendIdx << "]=" << *(currPend) << RESET << std::endl;
  std::cout << std::endl;

  std::cout << YELLOW << "  🎯 Search Bound Calculation for Leftover:" << RESET << std::endl;
  std::cout << "     Formula: main.size() - remaining_pend.size() + current_index + is_odd" << std::endl;
  std::cout << "     Calculation: " << mainChain.size() << " - " << remainingPendSize << " + " << pendIdx << " + " << (isOdd ? 1 : 0) << " = " << BOLD << searchBoundIdx << RESET << std::endl;
  std::cout << "     This ensures each leftover element searches an expanding window" << std::endl;
  std::cout << "     to maintain optimal binary search performance." << std::endl;
  std::cout << std::endl;

  // Show search space
  std::cout << "  " << BLUE << "🔍 Search space: " << RESET << "Main[0.." << searchBoundIdx << "]" << std::endl;

  size_t maxWidth = getMaxWidth(mainChain);

  // Print position markers above the array showing search bound
  // Account for opening bracket "["
  std::cout << "   ";  // 2 spaces for "  " before bracket, 1 for "["
  for (size_t i = 0; i < mainChain.size(); ++i)
  {
    if (i == searchBoundIdx + 1)
      std::cout << std::setw(maxWidth) << RED << "|" << RESET;
    else
      std::cout << std::setw(maxWidth) << " ";
    if (i < mainChain.size() - 1)
      std::cout << ", ";  // match the ", " spacing in the array
  }
  std::cout << std::endl;

  std::cout << "   ";  // 2 spaces for "  " before bracket, 1 for "["
  for (size_t i = 0; i < mainChain.size(); ++i)
  {
    if (i <= searchBoundIdx)
      std::cout << std::setw(maxWidth) << GREEN << "✓" << RESET;
    else
      std::cout << std::setw(maxWidth) << RED << "✗" << RESET;
    if (i < mainChain.size() - 1)
      std::cout << ", ";  // match the ", " spacing in the array
  }
  std::cout << "             (" << GREEN << "✓" << RESET << ") = searchable, (" << RED << "✗" << RESET << ") = not searchable" << std::endl;

  // Show insertion point
  size_t elementWidth = maxWidth + 2;
  size_t insertion_visual_index = insertionIndex * elementWidth;
  std::cout << "  ";
  for (size_t i = 0; i < insertion_visual_index; ++i)
    std::cout << " ";
  std::cout << YELLOW << "↓ insert here" << RESET << std::endl;

  // Show the main chain array
  std::cout << "  " << CYAN << "[";
  typedef typename std::vector<Iterator>::const_iterator const_iter;
  int available = mainChain.size();
  for (const_iter it = mainChain.begin(); it != mainChain.end(); ++it)
  {
    bool incomplete = (--available == 0);
    std::cout << std::setw(maxWidth) << *(*it);
    std::cout << (incomplete ? "" : ", ");
  }
  std::cout << "]" << RESET << std::endl;

  DEBUG_PRINT("  After insertion at position " << insertionIndex << ", main chain:" << std::endl << "  ");

  for (const_iter it = mainChain.begin(); it != mainChain.end(); ++it)
    std::cout << *(*it) << " ";
  std::cout << std::endl;
}

template <typename Iterator>
void printJacobsthalInfo(int k, int curr_jacobsthal, int jacobsthal_diff, const std::vector<Iterator> &main, const std::vector<Iterator> &pend)
{
  if (!g_verbose)
    return;

  std::cout << CYAN << "\n╔═════════════════════════════════════════════════════════════════════════════════╗" << RESET << std::endl;
  std::cout << CYAN << "║ " << RESET << YELLOW << BOLD << "Jacobsthal Round k=" << k << RESET << " / J(k) - J(k-1) ≤ pend.size() (current pend: " << pend.size() << ")" << CYAN << "            ║" << RESET << std::endl;
  std::cout << CYAN << "╚═════════════════════════════════════════════════════════════════════════════════╝" << RESET << std::endl;

  // Explain the insertion count formula
  std::cout << MAGENTA << "🔢 Insertion Count Formula:" << RESET << std::endl;
  std::cout << "   " << BOLD << curr_jacobsthal << " - " << _jacobsthal_number(k-1) << " = "
            << jacobsthal_diff << " insertion" << (jacobsthal_diff > 1 ? "s" : "") << RESET << std::endl;
  std::cout << std::endl;

  DEBUG_PRINT(YELLOW << "📋 Pend elements to insert this round (in reverse order):" << RESET << std::endl);
  printChains(main, pend, false, true, false);
}

template <typename Iterator>
void printInsertionHeader(const Iterator &pendElement, int pendIndex, int originalPendSize, int searchLimit, int curr_jacobsthal, int already_inserted)
{
  if (!g_verbose)
    return;

  std::cout << BOLD << MAGENTA << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << RESET << std::endl;
  std::cout << BOLD << MAGENTA << "→ Inserting pend[" << pendIndex
            << "]=" << *pendElement << RESET << " (originally position " << originalPendSize - pendIndex - 1 << " from end)"
            << std::endl;
  std::cout << BOLD << MAGENTA << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << RESET << std::endl;

  std::cout << YELLOW << "  🎯 Search Bound Calculation:" << RESET << std::endl;
  std::cout << "     Formula:     J(k) + already_inserted - 1" << std::endl;
  std::cout << "     Calculation: " << curr_jacobsthal << " + " << already_inserted << " - 1 = " << BOLD << searchLimit << RESET << std::endl;
  std::cout << std::endl;
}

#endif // PRINT_UTILS_HPP
