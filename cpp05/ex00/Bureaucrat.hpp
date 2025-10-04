#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <stdexcept>
#include <iostream>

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

    // Accessors
    const std::string &getName() const;
    int getGrade() const;

    // Member functions
    void incrementGrade();
    void decrementGrade();

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

// Overload of the insertion operator (ensuring a newline at the end)
std::ostream &operator<<(std::ostream &os, const Bureaucrat &bureaucrat);

#endif // BUREAUCRAT_HPP
