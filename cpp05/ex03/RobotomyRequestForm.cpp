#include "RobotomyRequestForm.hpp"
#include <iostream>

// Default constructor: sets a default target
RobotomyRequestForm::RobotomyRequestForm()
	: AForm("RobotomyRequestForm", 72, 45), target("default_target")
{}

// Parameterized constructor
RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
	: AForm("RobotomyRequestForm", 72, 45), target(target)
{}

// Copy constructor
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other)
	: AForm(other), target(other.target)
{}

// Copy assignment operator
RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		// 'target' is const and cannot be reassigned
	}
	return *this;
}

// Destructor
RobotomyRequestForm::~RobotomyRequestForm() {}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	if (!getIsSigned())
		throw FormNotSignedException();
	if (executor.getGrade() > getGradeRequiredToExecute())
		throw GradeTooLowException();

	std::cout << "Drilling noises... " << std::endl;
	if (std::rand() % 2 == 0)
	{
		std::cout << target << " has been successfully robotomized!" << std::endl;
	}
	else
	{
		std::cout << "Robotomy failed on " << target << "." << std::endl;
	}
}
