#ifndef INTERN_HPP
#define INTERN_HPP

#include <string>
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{
public:
	// Default constructor
	Intern();
	// Copy constructor
	Intern(const Intern &other);
	// Copy assignment operator
	Intern &operator=(const Intern &other);
	// Destructor
	~Intern();

	AForm *makeForm(const std::string &formName, const std::string &target);
};

#endif // INTERN_HPP
