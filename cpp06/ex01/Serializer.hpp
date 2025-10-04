#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include "Data.hpp"
#include <stdint.h>

class Serializer
{
private:
	// Private constructors to avoid any instantiation of Serializer
	Serializer();
	Serializer(const Serializer &);
	Serializer &operator=(const Serializer &);

public:
	static uintptr_t serialize(Data *ptr);
	static Data *deserialize(uintptr_t raw);
};

#endif
