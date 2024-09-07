#include "Zombie.hpp"
#include <new>

Zombie *zombieHorde(int N, std::string name)
{
	Zombie *horde = new Zombie[N];
	for (int i = 0; i < N; i++)
		if (!name.empty())
			horde[i].setName(name);
	return horde;
}
