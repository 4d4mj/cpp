#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <iomanip>
#include "Utils.hpp"

class ScalarConverter
{
private:
	ScalarConverter();									 // Private constructor (non-instantiable)
	ScalarConverter(const ScalarConverter &);			 // Private copy constructor
	ScalarConverter &operator=(const ScalarConverter &); // Private assignment operator

	static bool isChar(const std::string &input);
	static bool isInt(const std::string &input);
	static bool isFloat(const std::string &input);
	static bool isDouble(const std::string &input);

	static void printChar(double value);
	static void printInt(double value);
	static void printFloat(double value);
	static void printDouble(double value);

public:
	static void convert(const std::string &input);
};

#endif // SCALARCONVERTER_HPP
