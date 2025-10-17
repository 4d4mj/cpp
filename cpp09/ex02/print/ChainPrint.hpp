#ifndef CHAIN_PRINT_HPP
#define CHAIN_PRINT_HPP

#include <iostream>
#include <vector>
#include "Colors.hpp"
#include "PrintHelpers.hpp"

template <typename Iterator>
void printChains(const std::vector<Iterator> &mainChain, const std::vector<Iterator> &pendChain, bool onlyMain = false, bool onlyPend = false, bool useLabels = false)
{
  if (!g_verbose)
    return;

  int available = mainChain.size();
  if (!onlyPend)
  {
    if (useLabels)
    {
      print_detail::indentLevel(1);
      std::cout << BOLD << GREEN << "🏆 Winners (Main Chain):" << RESET << std::endl;
    }
    print_detail::indentLevel(useLabels ? 2 : 1);
    if (!useLabels)
      print_detail::indentAdditional(1);
    std::cout << "[";
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

  if (!onlyMain && !onlyPend)
    std::cout << std::endl;

  available = pendChain.size();
  if (useLabels)
  {
    print_detail::indentLevel(1);
    std::cout << BOLD << RED << "📌 Losers (Pend Chain):" << RESET << std::endl;
  }
  print_detail::indentLevel(useLabels ? 2 : 1);
  if (!useLabels)
    print_detail::indentAdditional(1);
  std::cout << "[";
  for (typename std::vector<Iterator>::const_iterator it = pendChain.begin(); it != pendChain.end(); ++it)
  {
    bool incomplete = (--available == 0);
    std::cout << RED << **it << RESET;
    std::cout << (incomplete ? "" : ", ");
  }
  std::cout << "]" << std::endl;
}

#endif // CHAIN_PRINT_HPP
