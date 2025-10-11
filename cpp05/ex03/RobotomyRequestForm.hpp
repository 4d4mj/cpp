#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include <cstdlib> // For rand()

class RobotomyRequestForm : public AForm
{
private:
	const std::string target;

public:
	// Default constructor
	RobotomyRequestForm();
	// Parameterized constructor
	RobotomyRequestForm(const std::string &target);
	// Copy constructor
	RobotomyRequestForm(const RobotomyRequestForm &other);
	// Copy assignment operator
	RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
	// Destructor
	~RobotomyRequestForm();

	void execute(Bureaucrat const &executor) const;
};

#endif // ROBOTOMYREQUESTFORM_HPP
