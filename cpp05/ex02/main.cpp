#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#include <cstdlib>
#include <ctime>

int main()
{
	std::srand(std::time(0));
	
	try
	{
		Bureaucrat alice("Alice", 1);
		ShrubberyCreationForm shrubbery("garden");
		RobotomyRequestForm robot("Bob");
		PresidentialPardonForm pardon("Charlie");

		shrubbery.beSigned(alice);
		alice.executeForm(shrubbery);

		robot.beSigned(alice);
		alice.executeForm(robot);

		pardon.beSigned(alice);
		alice.executeForm(pardon);
	}
	catch (const std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
