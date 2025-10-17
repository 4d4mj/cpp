#include "PrintHelpers.hpp"
#include "PrintLayout.hpp"
#include <iostream>

#ifdef VERBOSE
bool g_verbose = true;
#else
bool g_verbose = false;
#endif

void printOneTime(const std::string &msg)
{
	static bool printed = false;
	if (!g_verbose)
		return;

	if (printed || !g_verbose)
		return;

	std::cout << YELLOW << msg << RESET << std::endl;
	printed = true;
}

namespace print_detail
{
void indentLevel(std::size_t level, std::size_t spacesPerLevel)
{
  print_layout::indent(std::cout, level, spacesPerLevel);
}

void indentAdditional(std::size_t spaces)
{
  print_layout::indentSpaces(std::cout, spaces);
}
}
