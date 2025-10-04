#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <iostream>
#include <stdexcept>
#include "Bureaucrat.hpp"

class Bureaucrat; // Forward declaration

class AForm {
private:
    const std::string name;
    bool isSigned;
    const int gradeRequiredToSign;
    const int gradeRequiredToExecute;
public:
    // Default constructor
    AForm();
    // Parameterized constructor
    AForm(const std::string &name, int gradeRequiredToSign, int gradeRequiredToExecute);
    // Copy constructor
    AForm(const AForm &other);
    // Copy assignment operator
    AForm &operator=(const AForm &other);
    // Destructor
    virtual ~AForm();

    // Getters
    const std::string &getName() const;
    bool getIsSigned() const;
    int getGradeRequiredToSign() const;
    int getGradeRequiredToExecute() const;

    // Be signed by a Bureaucrat
    void beSigned(const Bureaucrat &bureaucrat);

    // Pure virtual function for executing the form's action
    virtual void execute(Bureaucrat const &executor) const = 0;

    // Exception classes
    class GradeTooHighException : public std::exception {
    public:
        virtual const char *what() const throw();
    };

    class GradeTooLowException : public std::exception {
    public:
        virtual const char *what() const throw();
    };

    class FormNotSignedException : public std::exception {
    public:
        virtual const char *what() const throw();
    };
};

std::ostream &operator<<(std::ostream &os, const AForm &form);

#endif // AFORM_HPP
