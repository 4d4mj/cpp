#ifndef SCALAR_UTILS_HPP
#define SCALAR_UTILS_HPP

#include <string>
#include <stdexcept>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <limits>

std::string mapEscape(const char c);
std::string removeQuotes(const std::string &input);
double preprocessInput(const std::string &input);

#endif
