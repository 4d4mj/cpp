#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm> // for std::find
#include <exception> // for std::exception

// The easyfind function template searches for 'value' in the container 'container'.
// If found, it returns an iterator to the first occurrence.
// Otherwise, it throws a std::exception.
template <typename T>
typename T::iterator easyfind(T &container, int value) {
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end()) {
        throw std::exception();
    }
    return it;
}

#endif // EASYFIND_HPP
