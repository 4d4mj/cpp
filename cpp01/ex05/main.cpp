#include "Harl.hpp"
#include <iostream>

int main()
{
	Harl harl;

	std::cout << "Test with DEBUG level:" << std::endl;
	harl.complain("DEBUG");

	std::cout << "\nTest with INFO level:" << std::endl;
	harl.complain("INFO");

	std::cout << "\nTest with WARNING level:" << std::endl;
	harl.complain("WARNING");

	std::cout << "\nTest with ERROR level:" << std::endl;
	harl.complain("ERROR");

	std::cout << "\nTest with invalid level:" << std::endl;
	harl.complain("INVALID");

	return 0;
}
