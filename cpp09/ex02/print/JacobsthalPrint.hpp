#ifndef JACOBSTHAL_PRINT_HPP
#define JACOBSTHAL_PRINT_HPP

#include <iostream>
#include <vector>
#include "Colors.hpp"
#include "PrintHelpers.hpp"
#include "ChainPrint.hpp"

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

#endif // JACOBSTHAL_PRINT_HPP
