#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main() {
    const Animal* animals[4];

    // Fill half with Dog objects and the other half with Cat objects
    animals[0] = new Dog();
    animals[1] = new Dog();
    animals[2] = new Cat();
    animals[3] = new Cat();

    // Test deep copy by copying one dog
    Dog dog1;
    dog1.getBrain()->setIdea(0, "Chase the ball");
    Dog dog2 = dog1;
    std::cout << "Dog2's brain first idea: " << dog2.getBrain()->getIdea(0) << std::endl;

    // Delete all animals
    for (int i = 0; i < 4; i++) {
        delete animals[i];
    }

    // Check for memory leaks after deleting all animals
    return 0;
}
