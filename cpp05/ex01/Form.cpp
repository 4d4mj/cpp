#include "Form.hpp"

// Default constructor: sets default values (all valid).
Form::Form() : name("Default"), isSigned(false), gradeRequiredToSign(150), gradeRequiredToExecute(150) {}

// Parameterized constructor
Form::Form(const std::string &name, int gradeRequiredToSign, int gradeRequiredToExecute)
    : name(name), isSigned(false), gradeRequiredToSign(gradeRequiredToSign), gradeRequiredToExecute(gradeRequiredToExecute)
{
    if (gradeRequiredToSign < 1 || gradeRequiredToExecute < 1)
        throw GradeTooHighException();
    if (gradeRequiredToSign > 150 || gradeRequiredToExecute > 150)
        throw GradeTooLowException();
}

// Copy constructor
Form::Form(const Form &other)
    : name(other.name),
      isSigned(other.isSigned),
      gradeRequiredToSign(other.gradeRequiredToSign),
      gradeRequiredToExecute(other.gradeRequiredToExecute)
{}

// Copy assignment operator
Form &Form::operator=(const Form &other) {
    if (this != &other) {
        // Only isSigned can be modified (all others are const).
        isSigned = other.isSigned;
    }
    return *this;
}

// Destructor
Form::~Form() {}

// Getters
const std::string &Form::getName() const {
    return name;
}

bool Form::getIsSigned() const {
    return isSigned;
}

int Form::getGradeRequiredToSign() const {
    return gradeRequiredToSign;
}

int Form::getGradeRequiredToExecute() const {
    return gradeRequiredToExecute;
}

// beSigned: signs the form if the Bureaucrat's grade is high enough.
void Form::beSigned(const Bureaucrat &bureaucrat) {
    if (bureaucrat.getGrade() > gradeRequiredToSign)
        throw GradeTooLowException();
    isSigned = true;
}

// Exception messages
const char *Form::GradeTooHighException::what() const throw() {
    return "Grade too high!";
}

const char *Form::GradeTooLowException::what() const throw() {
    return "Grade too low!";
}

// Overloaded insertion operator (ends with a newline)
std::ostream &operator<<(std::ostream &os, const Form &form) {
    os << "Form: " << form.getName()
       << ", Signed: " << (form.getIsSigned() ? "Yes" : "No")
       << ", Grade Required to Sign: " << form.getGradeRequiredToSign()
       << ", Grade Required to Execute: " << form.getGradeRequiredToExecute() << std::endl;
    return os;
}
