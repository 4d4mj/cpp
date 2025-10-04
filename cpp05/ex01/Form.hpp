#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <stdexcept>
#include <iostream>
#include "Bureaucrat.hpp"

class Form {
private:
    const std::string name;
    bool isSigned;
    const int gradeRequiredToSign;
    const int gradeRequiredToExecute;
public:
    // Default constructor
    Form();
    // Parameterized constructor
    Form(const std::string &name, int gradeRequiredToSign, int gradeRequiredToExecute);
    // Copy constructor
    Form(const Form &other);
    // Copy assignment operator
    Form &operator=(const Form &other);
    // Destructor
    ~Form();

    // Getters
    const std::string &getName() const;
    bool getIsSigned() const;
    int getGradeRequiredToSign() const;
    int getGradeRequiredToExecute() const;

    // Member function to be signed by a Bureaucrat
    void beSigned(const Bureaucrat &bureaucrat);

    // Exception classes
    class GradeTooHighException : public std::exception {
    public:
        virtual const char *what() const throw();
    };

    class GradeTooLowException : public std::exception {
    public:
        virtual const char *what() const throw();
    };
};

std::ostream &operator<<(std::ostream &os, const Form &form);

#endif // FORM_HPP
