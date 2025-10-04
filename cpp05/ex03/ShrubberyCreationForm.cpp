#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
	: AForm("ShrubberyCreationForm", 145, 137), target(target) {}

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

