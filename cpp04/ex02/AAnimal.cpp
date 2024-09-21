#include "AAnimal.hpp"

AAnimal::AAnimal() : type("Unknown AAnimal") {
    std::cout << "AAnimal created" << std::endl;
}

AAnimal::AAnimal(const AAnimal& other) : type(other.type) {
    std::cout << "AAnimal copy constructor called" << std::endl;
}

AAnimal& AAnimal::operator=(const AAnimal& other) {
    if (this != &other) {
        this->type = other.type;
    }
    std::cout << "AAnimal assignment operator called" << std::endl;
    return *this;
}

AAnimal::~AAnimal() {
    std::cout << "AAnimal destroyed" << std::endl;
}

std::string AAnimal::getType() const {
    return type;
}
