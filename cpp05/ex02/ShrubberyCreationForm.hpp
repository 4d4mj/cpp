#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <fstream>

class ShrubberyCreationForm : public AForm
{
private:
    const std::string target;
public:
    // Default constructor
    ShrubberyCreationForm();
    // Parameterized constructor
    ShrubberyCreationForm(const std::string &target);
    // Copy constructor
    ShrubberyCreationForm(const ShrubberyCreationForm &other);
    // Copy assignment operator
    ShrubberyCreationForm &operator=(const ShrubberyCreationForm &other);
    // Destructor
    ~ShrubberyCreationForm();

    // Overridden execute method
    void execute(Bureaucrat const &executor) const;
};

#endif // SHRUBBERYCREATIONFORM_HPP
