#ifndef INPUT_PARSER_HPP
#define INPUT_PARSER_HPP

#include <string>
#include <vector>
#include <deque>

// Validate command line arguments
std::string validateArgs(int argc, char **argv);

// Convert command line arguments to vector
std::vector<int> argvToVector(int argc, char **argv);

// Convert command line arguments to deque
std::deque<int> argvToDeque(int argc, char **argv);

#endif
