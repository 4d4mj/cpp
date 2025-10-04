#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <stdexcept>
#include <iostream>

class Form; // Forward declaration

class Bureaucrat {
private:
    const std::string name;
    int grade;
public:
    // Default constructor
    Bureaucrat();
    // Parameterized constructor
    Bureaucrat(const std::string &name, int grade);
    // Copy constructor
    Bureaucrat(const Bureaucrat &other);
    // Copy assignment operator
    Bureaucrat &operator=(const Bureaucrat &other);
    // Destructor
    ~Bureaucrat();

    // Getters
    const std::string &getName() const;
    int getGrade() const;

    // Grade manipulation
    void incrementGrade();
    void decrementGrade();

    // Sign form
    void signForm(Form &form);

    // Exception classes
    class GradeTooHighException : public std::exception {
    public:
        virtual const char* what() const throw();
    };

    class GradeTooLowException : public std::exception {
    public:
        virtual const char* what() const throw();
    };
};

std::ostream &operator<<(std::ostream &os, const Bureaucrat &bureaucrat);

#endif // BUREAUCRAT_HPP
