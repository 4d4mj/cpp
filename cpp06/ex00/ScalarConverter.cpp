#include "ScalarConverter.hpp"
#include "Utils.hpp"
#include <cerrno>
#include <cmath>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &) {}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &) { return *this; }
ScalarConverter::~ScalarConverter() {}

ScalarConverter::LiteralType ScalarConverter::detectLiteralType(const std::string &input)
{
	if (isPseudoLiteralFloat(input))
		return TYPE_PSEUDO_FLOAT;
	if (isPseudoLiteralDouble(input))
		return TYPE_PSEUDO_DOUBLE;
	if (isChar(input))
		return TYPE_CHAR;
	if (isInt(input))
		return TYPE_INT;
	if (isFloat(input))
		return TYPE_FLOAT;
	if (isDouble(input))
		return TYPE_DOUBLE;
	return TYPE_INVALID;
}

bool ScalarConverter::isPseudoLiteralFloat(const std::string &input)
{
	return (input == "-inff" || input == "+inff" || input == "nanf");
}

bool ScalarConverter::isPseudoLiteralDouble(const std::string &input)
{
	return (input == "-inf" || input == "+inf" || input == "nan");
}

bool ScalarConverter::isChar(const std::string &input)
{
	if (input.length() == 1 && std::isprint(static_cast<unsigned char>(input[0])) && !std::isdigit(static_cast<unsigned char>(input[0])))
		return true;

	try
	{
		std::string processed = removeQuotes(input);
		return processed.length() == 1;
	}
	catch (const std::exception &)
	{
		return false;
	}
}

bool ScalarConverter::isInt(const std::string &input)
{
	if (input.empty())
		return false;

	size_t idx = 0;
	if (input[idx] == '+' || input[idx] == '-')
		++idx;
	if (idx == input.length())
		return false;

	for (; idx < input.length(); ++idx)
	{
		if (!std::isdigit(static_cast<unsigned char>(input[idx])))
			return false;
	}

	char *end = NULL;
	errno = 0;
	long value = std::strtol(input.c_str(), &end, 10);
	if (errno == ERANGE || end == input.c_str() || *end != '\0')
		return false;

	return (value >= std::numeric_limits<int>::min() && value <= std::numeric_limits<int>::max());
}

bool ScalarConverter::isFloat(const std::string &input)
{
	if (input.size() < 2 || input[input.size() - 1] != 'f')
		return false;

	std::string core = input.substr(0, input.size() - 1);
	if (core.empty())
		return false;

	bool hasDigit = false;
	bool hasDot = false;
	for (size_t i = 0; i < core.size(); ++i)
	{
		char c = core[i];
		if ((c == '+' || c == '-') && i == 0)
			continue;
		if (std::isdigit(static_cast<unsigned char>(c)))
		{
			hasDigit = true;
			continue;
		}
		if (c == '.' && !hasDot)
		{
			hasDot = true;
			continue;
		}
		return false;
	}

	if (!hasDigit)
		return false;

	char *end = NULL;
	errno = 0;
	std::strtof(input.c_str(), &end);
	if (errno == ERANGE)
		return false;
	return (end != input.c_str() && *end == 'f' && *(end + 1) == '\0');
}

bool ScalarConverter::isDouble(const std::string &input)
{
	if (input.empty())
		return false;

	bool hasDigit = false;
	bool hasDot = false;
	for (size_t i = 0; i < input.size(); ++i)
	{
		char c = input[i];
		if ((c == '+' || c == '-') && i == 0)
			continue;
		if (std::isdigit(static_cast<unsigned char>(c)))
		{
			hasDigit = true;
			continue;
		}
		if (c == '.' && !hasDot)
		{
			hasDot = true;
			continue;
		}
		return false;
	}

	if (!hasDigit || !hasDot)
		return false;

	char *end = NULL;
	errno = 0;
	std::strtod(input.c_str(), &end);
	if (errno == ERANGE)
		return false;
	return (end != input.c_str() && *end == '\0');
}

char ScalarConverter::parseChar(const std::string &input)
{
	std::string processed = removeQuotes(input);
	if (processed.length() != 1)
		throw std::invalid_argument("Invalid char literal.");
	return processed[0];
}

int ScalarConverter::parseInt(const std::string &input)
{
	char *end = NULL;
	errno = 0;
	long value = std::strtol(input.c_str(), &end, 10);
	if (errno == ERANGE || end == input.c_str() || *end != '\0')
		throw std::out_of_range("Int literal out of range.");
	return static_cast<int>(value);
}

float ScalarConverter::parseFloat(const std::string &input)
{
	char *end = NULL;
	errno = 0;
	float value = std::strtof(input.c_str(), &end);
	if (errno == ERANGE || end == input.c_str() || *end != 'f' || *(end + 1) != '\0')
		throw std::out_of_range("Float literal out of range.");
	return value;
}

double ScalarConverter::parseDouble(const std::string &input)
{
	char *end = NULL;
	errno = 0;
	double value = std::strtod(input.c_str(), &end);
	if (errno == ERANGE || end == input.c_str() || *end != '\0')
		throw std::out_of_range("Double literal out of range.");
	return value;
}

std::string ScalarConverter::formatChar(long double value)
{
	if (std::isnan(value) || std::isinf(value) || value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max())
		return "char: impossible";

	char c = static_cast<char>(value);
	if (!std::isprint(static_cast<unsigned char>(c)))
		return "char: Non displayable";

	std::ostringstream oss;
	oss << "char: '" << c << "'";
	return oss.str();
}

std::string ScalarConverter::formatInt(long double value)
{
	if (std::isnan(value) || std::isinf(value) || value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
		return "int: impossible";

	std::ostringstream oss;
	oss << "int: " << static_cast<int>(value);
	return oss.str();
}

std::string ScalarConverter::formatFloat(float value)
{
	if (std::isnan(value))
		return "nanf";
	if (std::isinf(value))
		return (value > 0) ? "+inff" : "-inff";

	std::ostringstream oss;
	double integerPart = 0.0;
	if (std::modf(static_cast<double>(value), &integerPart) == 0.0)
	{
		oss << std::fixed << std::setprecision(1);
	}
	oss << value << 'f';
	return oss.str();
}

std::string ScalarConverter::formatDouble(double value)
{
	if (std::isnan(value))
		return "nan";
	if (std::isinf(value))
		return (value > 0) ? "+inf" : "-inf";

	std::ostringstream oss;
	double integerPart = 0.0;
	if (std::modf(value, &integerPart) == 0.0)
	{
		oss << std::fixed << std::setprecision(1);
	}
	oss << value;
	return oss.str();
}

void ScalarConverter::convert(const std::string &input)
{
	if (input.empty())
	{
		std::cout << "Error: Empty input is not valid." << std::endl;
		return;
	}

	LiteralType type = detectLiteralType(input);
	if (type == TYPE_INVALID)
	{
		std::cout << "Error: Literal type is not recognized." << std::endl;
		return;
	}

	if (type == TYPE_PSEUDO_FLOAT)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: " << input << std::endl;
		std::cout << "double: " << input.substr(0, input.size() - 1) << std::endl;
		return;
	}
	if (type == TYPE_PSEUDO_DOUBLE)
	{
		std::cout << "char: impossible" << std::endl;
		std::cout << "int: impossible" << std::endl;
		std::cout << "float: " << input << 'f' << std::endl;
		std::cout << "double: " << input << std::endl;
		return;
	}

	try
	{
		switch (type)
		{
		case TYPE_CHAR:
		{
			char c = parseChar(input);
			float fValue = static_cast<float>(c);
			double dValue = static_cast<double>(c);

			std::cout << formatChar(c) << std::endl;
			std::cout << formatInt(c) << std::endl;
			std::cout << "float: " << formatFloat(fValue) << std::endl;
			std::cout << "double: " << formatDouble(dValue) << std::endl;
			break;
		}
		case TYPE_INT:
		{
			int value = parseInt(input);
			float fValue = static_cast<float>(value);
			double dValue = static_cast<double>(value);

			std::cout << formatChar(value) << std::endl;
			std::cout << "int: " << value << std::endl;
			std::cout << "float: " << formatFloat(fValue) << std::endl;
			std::cout << "double: " << formatDouble(dValue) << std::endl;
			break;
		}
		case TYPE_FLOAT:
		{
			float value = parseFloat(input);
			double dValue = static_cast<double>(value);

			std::cout << formatChar(value) << std::endl;
			std::cout << formatInt(value) << std::endl;
			std::cout << "float: " << formatFloat(value) << std::endl;
			std::cout << "double: " << formatDouble(dValue) << std::endl;
			break;
		}
		case TYPE_DOUBLE:
		{
			double value = parseDouble(input);
			float fValue = static_cast<float>(value);

			std::cout << formatChar(value) << std::endl;
			std::cout << formatInt(value) << std::endl;
			std::cout << "float: " << formatFloat(fValue) << std::endl;
			std::cout << "double: " << formatDouble(value) << std::endl;
			break;
		}
		default:
			break;
		}
	}
	catch (const std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}
