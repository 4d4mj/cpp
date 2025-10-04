#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	try
	{
		Bureaucrat b1("Alice", 5);
		Form f1("FormA", 3, 5);

		std::cout << f1 << std::endl;

		b1.signForm(f1); // Alice couldn’t sign FormA because Grade too low!
		std::cout << f1 << std::endl;

		Bureaucrat b2("Bob", 2);
		b2.signForm(f1); // Bob signed FormA
		std::cout << f1 << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
