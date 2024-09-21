#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
private:
	int _value;
	static const int _fractionalBits = 8;

public:
	// Constructors and Destructor
	Fixed();
	Fixed(const int integer);
	Fixed(const float number);
	Fixed(const Fixed &other);
	~Fixed();

	// Operator Overloads
	Fixed &operator=(const Fixed &other);

	// Comparison Operators
	bool operator>(const Fixed &other) const;
	bool operator<(const Fixed &other) const;
	bool operator>=(const Fixed &other) const;
	bool operator<=(const Fixed &other) const;
	bool operator==(const Fixed &other) const;
	bool operator!=(const Fixed &other) const;

	// Arithmetic Operators
	Fixed operator+(const Fixed &other) const;
	Fixed operator-(const Fixed &other) const;
	Fixed operator*(const Fixed &other) const;
	Fixed operator/(const Fixed &other) const;

	// Increment and Decrement Operators
	Fixed &operator++();   // Pre-increment
	Fixed operator++(int); // Post-increment
	Fixed &operator--();   // Pre-decrement
	Fixed operator--(int); // Post-decrement

	// Getters and Setters
	int getRawBits(void) const;
	void setRawBits(int const raw);

	// Conversion functions
	float toFloat(void) const;
	int toInt(void) const;

	// Static Min and Max functions
	static Fixed &min(Fixed &a, Fixed &b);
	static const Fixed &min(const Fixed &a, const Fixed &b);
	static Fixed &max(Fixed &a, Fixed &b);
	static const Fixed &max(const Fixed &a, const Fixed &b);
};

// Overload for the << operator
std::ostream &operator<<(std::ostream &out, const Fixed &fixed);

#endif
