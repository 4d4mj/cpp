#include "Animal.hpp"

Animal::Animal() : type("Unknown Animal") {
    std::cout << "Animal created" << std::endl;
}

Animal::~Animal() {
    std::cout << "Animal destroyed" << std::endl;
}

std::string Animal::getType() const {
    return type;
}

void Animal::makeSound() const {
    std::cout << "Animal sound" << std::endl;
}
