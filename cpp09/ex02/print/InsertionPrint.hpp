#ifndef INSERTION_PRINT_HPP
#define INSERTION_PRINT_HPP

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "Colors.hpp"
#include "PrintHelpers.hpp"

namespace print_detail
{
template <typename Iterator>
std::size_t computeRangeCount(const std::vector<Iterator> &mainChain,
                              std::size_t boundExclusive,
                              bool treatBoundAsInclusive)
{
  return treatBoundAsInclusive ? std::min(boundExclusive + 1, mainChain.size())
                               : std::min(boundExclusive, mainChain.size());
}

inline std::size_t computeLastLabelIndex(std::size_t boundExclusive,
                                         bool treatBoundAsInclusive,
                                         std::size_t rangeCount)
{
  if (rangeCount == 0)
    return 0;
  if (treatBoundAsInclusive)
    return boundExclusive;
  if (boundExclusive == 0)
    return 0;
  return boundExclusive - 1;
}

template <typename Iterator>
void printSearchSpace(const std::vector<Iterator> &mainChain,
                      std::size_t boundExclusive,
                      bool treatBoundAsInclusive,
                      std::size_t indentLevelValue)
{
  indentLevel(indentLevelValue);
  std::size_t rangeCount = computeRangeCount(mainChain, boundExclusive, treatBoundAsInclusive);
  std::size_t lastLabel = computeLastLabelIndex(boundExclusive, treatBoundAsInclusive, rangeCount);

  std::cout << BLUE << "🔍 Search space: " << RESET
            << "Main[0.." << lastLabel << "] = [";

  typename std::vector<Iterator>::const_iterator it = mainChain.begin();
  for (std::size_t i = 0; i < rangeCount && it != mainChain.end(); ++i, ++it)
  {
    if (i > 0)
      std::cout << ", ";
    std::cout << **it;
  }
  std::cout << "]" << std::endl;
}

template <typename Iterator>
void printBoundMarkers(const std::vector<Iterator> &mainChain,
                       std::size_t boundExclusive,
                       std::size_t indentLevelValue,
                       std::size_t width)
{
  indentLevel(indentLevelValue);
  for (std::size_t i = 0; i < mainChain.size(); ++i)
  {
    if (i == boundExclusive)
      std::cout << std::setw(width) << RED << "|" << RESET;
    else
      std::cout << std::setw(width) << " ";
    if (i < mainChain.size() - 1)
      std::cout << "  ";
  }
  std::cout << std::endl;
}

template <typename Iterator>
void printAvailabilityRow(const std::vector<Iterator> &mainChain,
                          std::size_t boundExclusive,
                          bool treatBoundAsInclusive,
                          std::size_t indentLevelValue,
                          std::size_t elementWidth)
{
  indentLevel(indentLevelValue);
  indentAdditional(1);
  for (std::size_t i = 0; i < mainChain.size(); ++i)
  {
    bool searchable = treatBoundAsInclusive ? (i <= boundExclusive) : (i < boundExclusive);
    std::cout << (searchable ? GREEN : RED)
              << std::setw(elementWidth)
              << (searchable ? "✓" : "✗")
              << RESET;
    if (i < mainChain.size() - 1)
      std::cout << "  ";
  }
  std::cout << std::endl;
}

template <typename Iterator>
void printMainChainLine(const std::vector<Iterator> &mainChain,
                        std::size_t indentLevelValue,
                        std::size_t width)
{
  indentLevel(indentLevelValue);
  std::cout << CYAN << "[";
  int remaining = mainChain.size();
  for (typename std::vector<Iterator>::const_iterator it = mainChain.begin(); it != mainChain.end(); ++it)
  {
    bool isLast = (--remaining == 0);
    std::cout << std::setw(width) << **it;
    if (!isLast)
      std::cout << ", ";
  }
  std::cout << "]" << RESET << std::endl;
}

inline void printInsertionArrow(std::size_t insertionIndex,
                                std::size_t elementWidth,
                                std::size_t indentLevelValue,
                                const std::string &label)
{
  indentLevel(indentLevelValue);
  std::size_t arrowOffset = insertionIndex * elementWidth;
  indentAdditional(arrowOffset);
  std::cout << YELLOW << label << RESET << std::endl;
}

template <typename Iterator>
void renderInsertionLayout(const std::vector<Iterator> &mainChain,
                           std::size_t boundExclusive,
                           std::size_t insertionIndex,
                           const std::string &arrowLabel,
                           bool treatBoundAsInclusive,
                           bool showLegend = false)
{
  if (!g_verbose)
    return;

  std::size_t maxWidth = getMaxWidth(mainChain);
  std::size_t elementWidth = maxWidth + 2;

  printSearchSpace(mainChain, boundExclusive, treatBoundAsInclusive, 1);
  printBoundMarkers(mainChain, boundExclusive, 1, maxWidth);
  printAvailabilityRow(mainChain, boundExclusive, treatBoundAsInclusive, 1, elementWidth);

  if (showLegend)
  {
    indentLevel(1);
    indentAdditional(1);
    std::cout << "             (" << GREEN << "✓" << RESET << ") = searchable, ("
              << RED << "✗" << RESET << ") = not searchable" << std::endl;
  }

  printInsertionArrow(insertionIndex, elementWidth, 1, arrowLabel);
  printMainChainLine(mainChain, 1, maxWidth);
  std::cout << std::endl;
}
} // namespace print_detail

template <typename Iterator>
void printInsertionVisual(const std::vector<Iterator> &mainChain, typename std::vector<Iterator>::const_iterator idx, typename std::vector<Iterator>::const_iterator searchBound)
{
  if (!g_verbose)
    return;

  std::size_t boundExclusive = std::distance(mainChain.begin(), searchBound);
  std::size_t insertionIndex = std::distance(mainChain.begin(), idx);

  print_detail::renderInsertionLayout(mainChain,
                                      boundExclusive,
                                      insertionIndex,
                                      "↓ insert here",
                                      false);
}

template <typename Iterator>
void printRemainingInsertion(const std::vector<Iterator> &mainChain,
                             const Iterator &currPend,
                             size_t insertionIndex,
                             size_t searchBoundExclusive,
                             size_t pendIdx)
{
  if (!g_verbose)
    return;

  std::cout << MAGENTA << "\n→ Inserting leftover pend[" << pendIdx << "]=" << *currPend << RESET << std::endl;

  print_detail::renderInsertionLayout(mainChain,
                                      searchBoundExclusive,
                                      insertionIndex,
                                      "↓ insert here",
                                      false);
}

template <typename Iterator>
void printAfterInsertion(const std::vector<Iterator> &mainChain, const std::vector<Iterator> &pendChain)
{
  if (!g_verbose)
    return;

  std::cout << "  After insertion:" << std::endl << "  ";
  printChains(mainChain, pendChain, true);
}

template <typename Iterator>
void printInsertionHeader(const Iterator &pendElement,
                          int pendIndex,
                          int originalPendSize,
                          int searchLimit,
                          int jacob_bound,
                          int buddy_bound)
{
  if (!g_verbose)
    return;

  std::cout << BOLD << MAGENTA << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << RESET << std::endl;
  std::cout << BOLD << MAGENTA << "→ Inserting pend[" << pendIndex
            << "]=" << *pendElement << RESET << " (originally position " << originalPendSize - pendIndex - 1 << " from end)"
            << std::endl;
  std::cout << BOLD << MAGENTA << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << RESET << std::endl;

  std::cout << YELLOW << "  🎯 Search Bound Calculation:" << RESET << std::endl;
  std::cout << "     Jacobsthal bound (high - 1):       " << jacob_bound << "  [high sequence: 3→7→15→31→…]" << std::endl;
  std::cout << "     Partner bound (stay before buddy): " << buddy_bound << std::endl;
  std::cout << "     Effective upper index:             min(" << jacob_bound << ", " << buddy_bound << ") = "
            << BOLD << searchLimit << RESET << std::endl;
  std::cout << std::endl;
}

#endif // INSERTION_PRINT_HPP
