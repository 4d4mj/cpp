#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(const std::string &name) : m_name(name), m_weapon(nullptr) {}

HumanB::HumanB(const std::string &name, Weapon *weapon)
	: m_name(name), m_weapon(weapon) {}

void HumanB::setWeapon(const Weapon &weapon)
{
	if (m_weapon)
	{
		delete m_weapon;
	}
	m_weapon = new Weapon(weapon);
}

HumanB::~HumanB()
{
	if (m_weapon)
	{
		delete m_weapon;
	}
}

void HumanB::attack() const
{
	if (m_weapon)
	{
		std::cout << m_name << " attacks with their " << m_weapon->getType() << std::endl;
	}
	else
	{
		std::cout << m_name << " has no weapon to attack with!" << std::endl;
	}
}
