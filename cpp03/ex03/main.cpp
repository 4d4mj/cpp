#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"

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

    // Test FragTrap
    FragTrap fragtrap("Fraggy");
    fragtrap.attack("target3");
    fragtrap.takeDamage(40);
    fragtrap.beRepaired(25);
    fragtrap.highFivesGuys();

    // Test DiamondTrap
    DiamondTrap diamondtrap("Diamy");
    diamondtrap.attack("target4");
    diamondtrap.takeDamage(50);
    diamondtrap.beRepaired(35);
    diamondtrap.whoAmI();

    return 0;
}
