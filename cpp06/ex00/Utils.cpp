#include "Utils.hpp"

std::string mapEscape(const char c)
{
	switch (c)
	{
	case 'n':
		return std::string(1, '\n');
	case 't':
		return std::string(1, '\t');
	case 'r':
		return std::string(1, '\r');
	case '\\':
		return std::string(1, '\\');
	case '\'':
		return std::string(1, '\'');
	default:
		throw std::invalid_argument("Invalid escape sequence.");
	}
}

std::string removeQuotes(const std::string &input)
{
	if (input.length() == 2 && input[0] == '\\')
		return mapEscape(input[1]);

	if (input.length() == 3 && input[0] == '\'' && input[2] == '\'')
		return std::string(1, input[1]);

	if (input.length() == 4 && input[0] == '\'' && input[1] == '\\' && input[3] == '\'')
		return mapEscape(input[2]);

	return input;
}

double preprocessInput(const std::string &input)
{
	if (input.empty())
		throw std::invalid_argument("Empty input is not valid.");

	std::string processed = removeQuotes(input);

	if (processed.empty())
		throw std::invalid_argument("Empty input is not valid.");

	if (processed == "-inf")
		return -std::numeric_limits<double>::infinity();
	if (processed == "+inf")
		return std::numeric_limits<double>::infinity();
	if (processed == "nan")
		return std::numeric_limits<double>::quiet_NaN();
	if (processed == "-inff")
		return -std::numeric_limits<float>::infinity();
	if (processed == "+inff")
		return std::numeric_limits<float>::infinity();
	if (processed == "nanf")
		return std::numeric_limits<float>::quiet_NaN();

	// Handle float literals ending with 'f'
	if (processed[processed.size() - 1] == 'f')

	{
		processed.resize(processed.size() - 1);
		char *end;
		double value = std::strtod(processed.c_str(), &end);
		if (*end != '\0')
			throw std::invalid_argument("Invalid numeric input.");
		return value;
	}

	// Handle single characters
	if (processed.length() == 1)
		return static_cast<double>(processed[0]);

	// Convert string to double using std::strtod
	char *end;
	double value = std::strtod(processed.c_str(), &end);
	if (*end != '\0')
		throw std::invalid_argument("Invalid numeric input.");
	return value;
}

