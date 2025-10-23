#include "Parser.hpp"
#include <cerrno>
#include <climits>
#include <cstdlib>

// Validate a single argument
static std::string validateArg(const std::string &arg)
{
    if (arg[0] == '-')
        return "Negative numbers are not allowed";

    long nbr = strtol(arg.c_str(), NULL, 10);
    if (nbr == 0 && arg != "0")
        return "Non-number arguments not allowed";
    if (nbr > INT_MAX || errno == ERANGE)
        return "Too big arguments are not allowed";

    return "";
}

// Validate all command line arguments
std::string validateArgs(int argc, char **argv)
{
    if (argc == 1)
        return "No arguments were provided";

    for (int i = 1; i < argc; i++)
    {
        std::string status = validateArg(argv[i]);
        if (status != "")
            return status;
    }

    return "";
}

// Convert arguments to vector
std::vector<int> argvToVector(int argc, char **argv)
{
    std::vector<int> result;
    result.reserve(argc - 1);

    for (int i = 1; i < argc; i++)
        result.push_back(atoi(argv[i]));

    return result;
}

// Convert arguments to deque
std::deque<int> argvToDeque(int argc, char **argv)
{
    std::deque<int> result;

    for (int i = 1; i < argc; i++)
        result.push_back(atoi(argv[i]));

    return result;
}
