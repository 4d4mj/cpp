#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <string>
#include <iostream>

class ClapTrap
{
protected:
	std::string name;
	int hitPoints;
	int energyPoints;
	int attackDamage;

public:
	// Constructor
	ClapTrap(const std::string &name);

	// Destructor
	~ClapTrap();

	// Copy Constructor
	ClapTrap(const ClapTrap &other);

	// Assignment operator
	ClapTrap &operator=(const ClapTrap &other);

	// Public member functions
	void attack(const std::string &target);
	void takeDamage(unsigned int amount);
	void beRepaired(unsigned int amount);
};

#endif
