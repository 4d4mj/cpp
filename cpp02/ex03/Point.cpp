// Point.cpp
#include "Point.hpp"

// Default constructor, initializes x and y to 0
Point::Point() : x(0), y(0) {}

// Constructor that initializes x and y with given floating point numbers
Point::Point(const float x_val, const float y_val) : x(Fixed(x_val)), y(Fixed(y_val)) {}

// Copy constructor
Point::Point(const Point &other) : x(other.x), y(other.y) {}

// Assignment operator overload
Point &Point::operator=(const Point &other)
{
	// No assignment for const members x and y, typically return *this
	return *this;
}

// Destructor
Point::~Point() {}

// Getters for x and y
Fixed Point::getX() const
{
	return x;
}

Fixed Point::getY() const
{
	return y;
}
