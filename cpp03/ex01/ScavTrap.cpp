#include "ScavTrap.hpp"

// Constructor
ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name) {
    hitPoints = 100;
    energyPoints = 50;
    attackDamage = 20;
    std::cout << "ScavTrap " << name << " is created with 100 HP, 50 Energy, and 20 Attack Damage!" << std::endl;
}

// Destructor
ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap " << name << " is destroyed!" << std::endl;
}

// Attack function (overrides ClapTrap's attack)
void ScavTrap::attack(const std::string& target) {
    if (hitPoints <= 0 || energyPoints <= 0) {
        std::cout << "ScavTrap " << name << " has no energy or hit points left to attack!" << std::endl;
        return;
    }
    std::cout << "ScavTrap " << name << " ferociously attacks " << target << ", causing " << attackDamage << " points of damage!" << std::endl;
    energyPoints--;
}

// Special ability: guardGate
void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << name << " is now in Gatekeeper mode!" << std::endl;
}
