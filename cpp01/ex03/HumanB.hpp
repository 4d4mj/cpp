#ifndef HUMANB_HPP
#define HUMANB_HPP

#include <string>
#include <iostream>
#include "Weapon.hpp"

class HumanB
{
public:
	HumanB(const std::string &name);
	HumanB(const std::string &name, Weapon *weapon);
	~HumanB();
	void setWeapon(const Weapon &weapon);
	void attack() const;

private:
	std::string m_name;
	Weapon *m_weapon;
};

#endif
