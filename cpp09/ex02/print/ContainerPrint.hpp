#ifndef CONTAINER_PRINT_HPP
#define CONTAINER_PRINT_HPP

#include <iostream>
#include <algorithm>
#include <iterator>
#include "Colors.hpp"
#include "PrintHelpers.hpp"

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

#endif // CONTAINER_PRINT_HPP
