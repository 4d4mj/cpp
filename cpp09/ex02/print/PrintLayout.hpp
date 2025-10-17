#ifndef PRINT_LAYOUT_HPP
#define PRINT_LAYOUT_HPP

#include <cstddef>
#include <iostream>
#include <string>

namespace print_layout
{
inline void indent(std::ostream &os, std::size_t level, std::size_t spacesPerLevel = 2)
{
    os << std::string(level * spacesPerLevel, ' ');
}

inline void indentSpaces(std::ostream &os, std::size_t count)
{
    os << std::string(count, ' ');
}
} // namespace print_layout

#endif // PRINT_LAYOUT_HPP
