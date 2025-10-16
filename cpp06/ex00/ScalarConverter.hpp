#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>

class ScalarConverter
{
private:
	ScalarConverter();
	ScalarConverter(const ScalarConverter &);
	ScalarConverter &operator=(const ScalarConverter &);
	~ScalarConverter();

	enum LiteralType
	{
		TYPE_CHAR,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_DOUBLE,
		TYPE_PSEUDO_FLOAT,
		TYPE_PSEUDO_DOUBLE,
		TYPE_INVALID
	};

	static LiteralType detectLiteralType(const std::string &input);
	static bool isChar(const std::string &input);
	static bool isInt(const std::string &input);
	static bool isFloat(const std::string &input);
	static bool isDouble(const std::string &input);
	static bool isPseudoLiteralFloat(const std::string &input);
	static bool isPseudoLiteralDouble(const std::string &input);

	static char parseChar(const std::string &input);
	static int parseInt(const std::string &input);
	static float parseFloat(const std::string &input);
	static double parseDouble(const std::string &input);

	static std::string formatChar(long double value);
	static std::string formatInt(long double value);
	static std::string formatFloat(float value);
	static std::string formatDouble(double value);

public:
	static void convert(const std::string &input);
};

#endif // SCALARCONVERTER_HPP
