#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
private:
    const std::string target;
public:
    // Default constructor
    PresidentialPardonForm();
    // Parameterized constructor
    PresidentialPardonForm(const std::string &target);
    // Copy constructor
    PresidentialPardonForm(const PresidentialPardonForm &other);
    // Copy assignment operator
    PresidentialPardonForm &operator=(const PresidentialPardonForm &other);
    // Destructor
    ~PresidentialPardonForm();

    // Overridden execute method
    void execute(Bureaucrat const &executor) const;
};

#endif // PRESIDENTIALPARDONFORM_HPP
