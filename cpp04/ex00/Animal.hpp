#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include <string>

class Animal
{
protected:
	std::string type;

public:
	Animal();
	virtual ~Animal(); // Virtual destructor
	std::string getType() const;
	virtual void makeSound() const; // Virtual function for polymorphism
};

#endif
