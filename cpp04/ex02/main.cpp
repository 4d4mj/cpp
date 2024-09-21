#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main() {
    // Test 1: Trying to instantiate AAnimal (should cause a compile error)
    // Uncommenting the line below should result in a compile error, which is expected.
    // const AAnimal* animal = new AAnimal(); // Should not compile!

    // Test 2: Instantiate Dog and Cat
    const AAnimal* j = new Dog();
    const AAnimal* i = new Cat();

    // Test 3: Check polymorphism (makeSound should call the correct function)
    j->makeSound(); // Should output "Bark!"
    i->makeSound(); // Should output "Meow!"

    // Clean up
    delete j;
    delete i;

    // Test 4: Deep copy test
    Dog dog1;
    dog1.getBrain()->setIdea(0, "Chase the ball");
    Dog dog2 = dog1;  // Copy constructor

    // Modify dog1's brain and check that dog2's brain is not affected
    dog1.getBrain()->setIdea(0, "Sleep all day");
    std::cout << "Dog1's brain first idea: " << dog1.getBrain()->getIdea(0) << std::endl;
    std::cout << "Dog2's brain first idea: " << dog2.getBrain()->getIdea(0) << std::endl;

    // Test 5: Array of animals (mixed Dog and Cat)
    const AAnimal* animals[4];
    animals[0] = new Dog();
    animals[1] = new Cat();
    animals[2] = new Dog();
    animals[3] = new Cat();

    // Ensure correct sound and no memory leak
    for (int k = 0; k < 4; k++) {
        animals[k]->makeSound();
    }

    // Delete animals (calls destructor for Dog/Cat and frees memory)
    for (int k = 0; k < 4; k++) {
        delete animals[k];
    }

    // Test 6: Check for memory leaks
    // Run the program with a memory checking tool such as Valgrind (Linux) or Dr. Memory (Windows).
    // Example command (Valgrind):
    // valgrind --leak-check=full ./animals

    return 0;
}
