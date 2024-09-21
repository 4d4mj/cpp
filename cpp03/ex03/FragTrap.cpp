#include "FragTrap.hpp"

// Constructor
FragTrap::FragTrap(const std::string& name) : ClapTrap(name) {
    hitPoints = 100;
    energyPoints = 100;
    attackDamage = 30;
    std::cout << "FragTrap " << name << " is created with 100 HP, 100 Energy, and 30 Attack Damage!" << std::endl;
}

// Destructor
FragTrap::~FragTrap() {
    std::cout << "FragTrap " << name << " is destroyed!" << std::endl;
}

// Attack function (overrides ClapTrap's attack)
void FragTrap::attack(const std::string& target) {
    if (hitPoints <= 0 || energyPoints <= 0) {
        std::cout << "FragTrap " << name << " has no energy or hit points left to attack!" << std::endl;
        return;
    }
    std::cout << "FragTrap " << name << " launches an attack on " << target << ", causing " << attackDamage << " points of damage!" << std::endl;
    energyPoints--;
}

// Special ability: highFivesGuys
void FragTrap::highFivesGuys() {
    std::cout << "FragTrap " << name << " asks for a high five! Positive vibes!" << std::endl;
}
