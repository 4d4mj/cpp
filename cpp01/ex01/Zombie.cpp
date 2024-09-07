#include "Zombie.hpp"

Zombie::Zombie() : name("An unnamed zombie") {}

Zombie::Zombie(std::string z_name) : name(z_name) {}

Zombie::~Zombie()
{
	std::cout << name << " is destroyed." << std::endl;
}

void Zombie::setName(std::string& z_name)
{
	if (z_name.empty())
		name = "An unnamed zombie";
	else
		name = z_name;
}

void Zombie::announce(void) const
{
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

