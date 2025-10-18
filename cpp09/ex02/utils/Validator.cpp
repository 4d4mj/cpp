#include "Validator.hpp"
#include <algorithm>

// Verify that sorted result contains the same values as original
bool retainedOriginalValues(const std::vector<int> &original,
                            const std::vector<int> &sorted)
{
    if (original.size() != sorted.size())
        return false;

    // Create copies for comparison
    std::vector<int> origCopy = original;
    std::vector<int> sortedCopy = sorted;

    // Sort both to compare
    std::sort(origCopy.begin(), origCopy.end());
    std::sort(sortedCopy.begin(), sortedCopy.end());

    // Compare element by element
    for (std::size_t i = 0; i < origCopy.size(); ++i)
    {
        if (origCopy[i] != sortedCopy[i])
            return false;
    }

    return true;
}
