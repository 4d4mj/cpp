#include "DequeSort.hpp"
#include "../utils/Jacobsthal.hpp"
#include <algorithm>

// Wrap integers with indices
std::deque<DequeElement> wrapDequeWithIndices(const std::deque<int> &data)
{
    std::deque<DequeElement> elements;

    for (std::size_t i = 0; i < data.size(); ++i)
        elements.push_back(DequeElement(data[i], i));

    return elements;
}

// Unwrap elements back to integers
std::deque<int> unwrapDequeElements(const std::deque<DequeElement> &elements)
{
    std::deque<int> result;

    for (std::size_t i = 0; i < elements.size(); ++i)
        result.push_back(elements[i].value);

    return result;
}

// Pair and sort elements
void pairAndSortDequeElements(const std::deque<DequeElement> &data,
                               std::deque<DequeElement> &main,
                               std::deque<DequeElement> &pend,
                               int &compCount)
{
    main.clear();
    pend.clear();

    // Process pairs
    for (std::size_t i = 0; i + 1 < data.size(); i += 2)
    {
        if (compareDequeElements(data[i], data[i + 1], compCount))
        {
            main.push_back(data[i]);
            pend.push_back(data[i + 1]);
        }
        else
        {
            main.push_back(data[i + 1]);
            pend.push_back(data[i]);
        }
    }

    // Handle odd element
    if (data.size() % 2 == 1)
        pend.push_back(data.back());
}

// Reorder pend to match sorted main
std::deque<DequeElement> reorderDequePend(const std::deque<DequeElement> &originalMain,
                                          const std::deque<DequeElement> &sortedMain,
                                          const std::deque<DequeElement> &originalPend)
{
    std::deque<DequeElement> reorderedPend;

    // For each element in sorted main, find its original pair in pend
    for (std::size_t i = 0; i < sortedMain.size(); ++i)
    {
        // Find where this element was in original main
        for (std::size_t j = 0; j < originalMain.size(); ++j)
        {
            if (originalMain[j].index == sortedMain[i].index)
            {
                reorderedPend.push_back(originalPend[j]);
                break;
            }
        }
    }

    // Add the odd element if it exists
    if (originalPend.size() > originalMain.size())
        reorderedPend.push_back(originalPend.back());

    return reorderedPend;
}

// Binary search for insertion position
int binarySearchDeque(const std::deque<DequeElement> &main,
                      const DequeElement &pend,
                      int high,
                      int &compCount)
{
    if (main.empty())
        return 0;

    if (high >= static_cast<int>(main.size()))
        high = static_cast<int>(main.size()) - 1;

    int low = 0;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        ++compCount;

        if (main[mid].value == pend.value)
        {
            // Handle equal values by comparing indices
            if (pend.index < main[mid].index)
                high = mid - 1;
            else if (pend.index > main[mid].index)
                low = mid + 1;
            else
                return mid;
        }
        else if (main[mid].value > pend.value)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    // Determine final insertion position
    if (low < static_cast<int>(main.size()))
    {
        if (pend.value < main[low].value)
            return low;
        if (pend.value == main[low].value && pend.index < main[low].index)
            return low;
    }

    return static_cast<int>(main.size());
}

// Insert pend elements using Jacobsthal order
void insertDequePendIntoMain(std::deque<DequeElement> &main,
                             const std::deque<DequeElement> &pend,
                             int &compCount)
{
    if (pend.empty())
        return;

    // Insert first pend element at the beginning
    main.insert(main.begin(), pend[0]);

    // Build Jacobsthal insertion order
    std::vector<int> insertionOrder = buildInsertionOrder(pend.size());

    int high = 3; // Initial search range

    for (std::size_t i = 0; i < insertionOrder.size(); ++i)
    {
        int pendIndex = insertionOrder[i];

        // Update search range at Jacobsthal boundaries
        if (i > 0 && insertionOrder[i] > insertionOrder[i - 1])
            high = 2 * high + 1;

        // Skip index 1 (already inserted)
        if (pendIndex <= static_cast<int>(pend.size()) && pendIndex != 1)
        {
            int insertPos = binarySearchDeque(main, pend[pendIndex - 1], high - 1, compCount);
            main.insert(main.begin() + insertPos, pend[pendIndex - 1]);
        }
    }
}

// Recursive Ford-Johnson sort
std::deque<DequeElement> fordJohnsonSortDequeRecursive(
    const std::deque<DequeElement> &data,
    int &compCount)
{
    // Base cases
    if (data.empty())
        return std::deque<DequeElement>();

    if (data.size() == 1)
        return data;

    if (data.size() == 2)
    {
        std::deque<DequeElement> result = data;
        if (compareDequeElements(result[0], result[1], compCount))
            std::swap(result[0], result[1]);
        return result;
    }

    // Pair and sort
    std::deque<DequeElement> main, pend;
    pairAndSortDequeElements(data, main, pend, compCount);

    // Recursively sort main chain
    std::deque<DequeElement> sortedMain = fordJohnsonSortDequeRecursive(main, compCount);

    // Reorder pend to match sorted main
    std::deque<DequeElement> reorderedPend = reorderDequePend(main, sortedMain, pend);

    // Insert pend into main
    insertDequePendIntoMain(sortedMain, reorderedPend, compCount);

    return sortedMain;
}

// Main entry point
void fordJohnsonSortDeque(std::deque<int> &deq, int &compCount)
{
    if (deq.size() <= 1)
        return;

    std::deque<DequeElement> wrapped = wrapDequeWithIndices(deq);
    std::deque<DequeElement> sorted = fordJohnsonSortDequeRecursive(wrapped, compCount);
    deq = unwrapDequeElements(sorted);
}
