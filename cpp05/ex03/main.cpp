#include "Intern.hpp"
#include "Bureaucrat.hpp"

int main()
{
	try
	{
		Intern someRandomIntern;
		Bureaucrat alice("Alice", 1);

		AForm *shrubbery = someRandomIntern.makeForm("shrubbery creation", "garden");
		AForm *robotomy = someRandomIntern.makeForm("robotomy request", "Bender");
		AForm *pardon = someRandomIntern.makeForm("presidential pardon", "Fry");
		AForm *unknown = someRandomIntern.makeForm("unknown form", "Zoidberg");

		if (shrubbery)
		{
			shrubbery->beSigned(alice);
			alice.executeForm(*shrubbery);
			delete shrubbery;
		}

		if (robotomy)
		{
			robotomy->beSigned(alice);
			alice.executeForm(*robotomy);
			delete robotomy;
		}

		if (pardon)
		{
			pardon->beSigned(alice);
			alice.executeForm(*pardon);
			delete pardon;
		}

		if (unknown)
		{
			delete unknown;
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
