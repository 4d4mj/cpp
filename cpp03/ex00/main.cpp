#include "ClapTrap.hpp"

int main()
{
	ClapTrap claptrap("Clappy");

	claptrap.attack("target1");
	claptrap.takeDamage(3);
	claptrap.beRepaired(5);

	claptrap.attack("target2");
	claptrap.takeDamage(8);
	claptrap.beRepaired(3);

	return 0;
}
