#include "PrintUtils.hpp"

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

