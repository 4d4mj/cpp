#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap {
public:
    // Constructor
    FragTrap(const std::string& name);

    // Destructor
    ~FragTrap();

    // Public member functions
    void attack(const std::string& target);
    void highFivesGuys();
};

#endif
