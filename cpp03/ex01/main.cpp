#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main() {
    // Test ClapTrap
    ClapTrap claptrap("Clappy");
    claptrap.attack("target1");
    claptrap.takeDamage(3);
    claptrap.beRepaired(5);

    // Test ScavTrap
    ScavTrap scavtrap("Scavy");
    scavtrap.attack("target2");
    scavtrap.takeDamage(30);
    scavtrap.beRepaired(20);
    scavtrap.guardGate();

    return 0;
}
