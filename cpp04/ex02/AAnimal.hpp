#ifndef AANIMAL_HPP
#define AANIMAL_HPP

#include <iostream>
#include <string>

class AAnimal {
protected:
    std::string type;

public:
    AAnimal();
    AAnimal(const AAnimal& other);
    AAnimal& operator=(const AAnimal& other);
    virtual ~AAnimal(); // Virtual destructor

    std::string getType() const;

    // Pure virtual function to make the class abstract
    virtual void makeSound() const = 0;
};

#endif
