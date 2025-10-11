#include "ShrubberyCreationForm.hpp"

// Default constructor: sets a default target
ShrubberyCreationForm::ShrubberyCreationForm()
	: AForm("ShrubberyCreationForm", 145, 137), target("default_target")
{}

// Parameterized constructor
ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
	: AForm("ShrubberyCreationForm", 145, 137), target(target)
{}

// Copy constructor
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
	: AForm(other), target(other.target)
{}

// Copy assignment operator
ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
	if (this != &other)
	{
		// Call base class assignment operator (this will update mutable members)
		AForm::operator=(other);
		// 'target' is const and cannot be reassigned
	}
	return *this;
}

// Destructor
ShrubberyCreationForm::~ShrubberyCreationForm() {}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const {
    if (!getIsSigned())
        throw FormNotSignedException();
    if (executor.getGrade() > getGradeRequiredToExecute())
        throw GradeTooLowException();

    std::ofstream file((target + "_shrubbery").c_str());
    if (!file) {
        throw std::ios_base::failure("Failed to open file.");
    }

    file << "       _-_       \n"
         << "    /~~   ~~\\    \n"
         << " /~~         ~~\\ \n"
         << "{               }\n"
         << " \\  _-     -_  / \n"
         << "   ~  \\\\ //  ~   \n"
         << "_- -   | | _- _  \n"
         << "  _ -  | |   -_  \n"
         << "      // \\\\      \n";
    file.close();
}

