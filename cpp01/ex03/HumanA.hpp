#ifndef HUMANA_HPP
#define HUMANA_HPP

#include <string>
#include <iostream>
#include "Weapon.hpp"

class HumanA
{
public:
	HumanA(const std::string &name, Weapon &weapon);
	~HumanA();
	void attack() const;

private:
	std::string m_name;
	Weapon &m_weapon;
};

#endif
