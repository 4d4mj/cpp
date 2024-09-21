#include "DiamondTrap.hpp"

// Constructor
DiamondTrap::DiamondTrap(const std::string& name)
    : ClapTrap(name + "_clap_name"), FragTrap(name), ScavTrap(name), name(name) {
    hitPoints = FragTrap::hitPoints;  // From FragTrap
    energyPoints = ScavTrap::energyPoints; // From ScavTrap
    attackDamage = FragTrap::attackDamage; // From FragTrap

    std::cout << "DiamondTrap " << this->name << " is created with " << hitPoints
              << " HP, " << energyPoints << " Energy, and " << attackDamage
              << " Attack Damage!" << std::endl;
}

// Destructor
DiamondTrap::~DiamondTrap() {
    std::cout << "DiamondTrap " << name << " is destroyed!" << std::endl;
}

// Use ScavTrap's attack method
void DiamondTrap::attack(const std::string& target) {
    ClapTrap::attack(target);  // Use ScavTrap's attack function
}

void DiamondTrap::takeDamage(unsigned int amount) {
	ClapTrap::takeDamage(amount);
}

void DiamondTrap::beRepaired(unsigned int amount) {
	ClapTrap::beRepaired(amount);
}

// Special whoAmI function to display both DiamondTrap's and ClapTrap's name
void DiamondTrap::whoAmI() {
    std::cout << "DiamondTrap name is: " << name << " and ClapTrap name is: "
              << ClapTrap::name << std::endl;
}
