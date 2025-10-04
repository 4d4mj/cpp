#include "RobotomyRequestForm.hpp"
#include <iostream>

RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
	: AForm("RobotomyRequestForm", 72, 45), target(target) {}

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
