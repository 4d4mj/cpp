#include "AForm.hpp"

// Default constructor: sets default values (all valid)
AForm::AForm()
	: name("Default"), isSigned(false), gradeRequiredToSign(150), gradeRequiredToExecute(150)
{}

// Parameterized constructor
AForm::AForm(const std::string &name, int gradeRequiredToSign, int gradeRequiredToExecute)
	: name(name), isSigned(false), gradeRequiredToSign(gradeRequiredToSign), gradeRequiredToExecute(gradeRequiredToExecute)
{
	if (gradeRequiredToSign < 1 || gradeRequiredToExecute < 1)
		throw GradeTooHighException();
	if (gradeRequiredToSign > 150 || gradeRequiredToExecute > 150)
		throw GradeTooLowException();
}

// Copy constructor
AForm::AForm(const AForm &other)
	: name(other.name),
	  isSigned(other.isSigned),
	  gradeRequiredToSign(other.gradeRequiredToSign),
	  gradeRequiredToExecute(other.gradeRequiredToExecute)
{}

// Copy assignment operator
AForm &AForm::operator=(const AForm &other)
{
	if (this != &other)
	{
		// Only the mutable member (isSigned) can be assigned
		isSigned = other.isSigned;
	}
	return *this;
}

// Destructor
AForm::~AForm() {}

const std::string &AForm::getName() const
{
	return name;
}

bool AForm::getIsSigned() const
{
	return isSigned;
}

int AForm::getGradeRequiredToSign() const
{
	return gradeRequiredToSign;
}

int AForm::getGradeRequiredToExecute() const
{
	return gradeRequiredToExecute;
}

void AForm::beSigned(const Bureaucrat &bureaucrat)
{
	if (bureaucrat.getGrade() > gradeRequiredToSign)
		throw GradeTooLowException();
	isSigned = true;
}

const char *AForm::GradeTooHighException::what() const throw()
{
	return "Grade too high!";
}

const char *AForm::GradeTooLowException::what() const throw()
{
	return "Grade too low!";
}

const char *AForm::FormNotSignedException::what() const throw()
{
	return "Form not signed!";
}

std::ostream &operator<<(std::ostream &os, const AForm &form)
{
	os << "Form: " << form.getName()
	   << ", Signed: " << (form.getIsSigned() ? "Yes" : "No")
	   << ", Grade Required to Sign: " << form.getGradeRequiredToSign()
	   << ", Grade Required to Execute: " << form.getGradeRequiredToExecute();
	return os;
}
