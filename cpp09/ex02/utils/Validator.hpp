#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include <vector>

// Check if a container is sorted in ascending order
template <typename T>
bool isSorted(const T &container)
{
    if (container.size() == 0 || container.size() == 1)
        return true;

    typename T::const_iterator end = container.end();
    std::advance(end, -1);

    for (typename T::const_iterator it = container.begin(); it != end; it++)
    {
        typename T::const_iterator next = it;
        std::advance(next, 1);
        if (*it > *next)
            return false;
    }

    return true;
}

// Verify that the sorted result contains the same values as the original
bool retainedOriginalValues(const std::vector<int> &original,
                            const std::vector<int> &sorted);

#endif
