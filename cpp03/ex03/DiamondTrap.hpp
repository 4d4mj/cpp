#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap : public FragTrap, public ScavTrap {
private:
    std::string name;  // Shadows ClapTrap::name

public:
    // Constructor
    DiamondTrap(const std::string& name);

    // Destructor
    ~DiamondTrap();

    // Public member functions
    void attack(const std::string& target);  // ScavTrap's attack
	void takeDamage(unsigned int amount);  // FragTrap's takeDamage
	void beRepaired(unsigned int amount);  // FragTrap's beRepaired
    void whoAmI();
};

#endif
