#include "Intern.hpp"
#include <iostream>

// Default constructor
Intern::Intern() {}

// Copy constructor
Intern::Intern(const Intern &other) {
	(void)other; // Intern has no attributes to copy
}

// Copy assignment operator
Intern &Intern::operator=(const Intern &other) {
	(void)other; // Intern has no attributes to copy
	return *this;
}

// Destructor
Intern::~Intern() {}

// Helper functions to create specific forms
static AForm *createShrubbery(const std::string &target)
{
	return new ShrubberyCreationForm(target);
}

static AForm *createRobotomy(const std::string &target)
{
	return new RobotomyRequestForm(target);
}

static AForm *createPresidential(const std::string &target)
{
	return new PresidentialPardonForm(target);
}

AForm *Intern::makeForm(const std::string &formName, const std::string &target)
{
	const std::string formNames[] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"};

	AForm *(*formCreators[])(const std::string &) = {
		createShrubbery,
		createRobotomy,
		createPresidential};

	for (size_t i = 0; i < 3; ++i)
	{
		if (formName == formNames[i])
		{
			std::cout << "Intern creates " << formName << std::endl;
			return formCreators[i](target);
		}
	}

	std::cout << "Error: Form name \"" << formName << "\" not recognized." << std::endl;
	return NULL;
}
