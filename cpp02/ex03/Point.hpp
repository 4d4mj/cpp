// Point.hpp
#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

class Point
{
private:
	const Fixed x;
	const Fixed y;

public:
	// Constructors
	Point();									 // Default constructor
	Point(const float x_val, const float y_val); // Constructor with two floats
	Point(const Point &other);					 // Copy constructor

	// Assignment operator overload
	Point &operator=(const Point &other);

	// Destructor
	~Point();

	// Getters for x and y coordinates
	Fixed getX() const;
	Fixed getY() const;
};

#endif
