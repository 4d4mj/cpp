#include "Jacobsthal.hpp"
#include <algorithm>

// Calculate a single Jacobsthal number iteratively
long calculateJacobsthalNumber(long n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    long prev2 = 0; // J(0)
    long prev1 = 1; // J(1)
    long curr = 0;

    for (long i = 2; i <= n; ++i)
    {
        curr = prev1 + 2 * prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return curr;
}

// Generate Jacobsthal sequence starting from J(3)
std::vector<int> generateJacobsthalSequence(std::size_t size)
{
    std::vector<int> sequence;
    int index = 3;

    while (true)
    {
        long value = calculateJacobsthalNumber(index);
        if (value > static_cast<long>(size))
            break;
        sequence.push_back(static_cast<int>(value));
        index++;
    }

    return sequence;
}

// Fill indices backward from each Jacobsthal number
void fillBackwardFromJacobsthal(std::vector<int> &result,
                                 const std::vector<int> &jacobSequence)
{
    std::vector<int> alreadyPushed;

    for (std::vector<int>::const_iterator it = jacobSequence.begin();
         it != jacobSequence.end();
         ++it)
    {
        int jacobNum = *it;

        // Fill backward from jacobNum down to (previous jacobNum + 1)
        while (jacobNum > 1)
        {
            // Check if we already pushed this number
            if (std::find(alreadyPushed.begin(), alreadyPushed.end(), jacobNum)
                == alreadyPushed.end())
            {
                result.push_back(jacobNum);
                alreadyPushed.push_back(jacobNum);
            }
            else
            {
                // We hit a number from a previous range, stop
                break;
            }
            --jacobNum;
        }
    }
}

// Fill remaining indices that weren't covered by Jacobsthal ranges
void fillRemainingIndices(std::vector<int> &result, std::size_t totalSize)
{
    std::vector<int> alreadyInResult = result;
    int currentNum = static_cast<int>(totalSize);

    while (result.size() < totalSize)
    {
        if (std::find(alreadyInResult.begin(), alreadyInResult.end(), currentNum)
            == alreadyInResult.end())
        {
            result.push_back(currentNum);
            alreadyInResult.push_back(currentNum);
        }
        --currentNum;

        if (currentNum < 1)
            break;
    }
}

// Build complete insertion order
std::vector<int> buildInsertionOrder(std::size_t pendSize)
{
    if (pendSize == 0)
        return std::vector<int>();

    std::vector<int> jacobSequence = generateJacobsthalSequence(pendSize);
    std::vector<int> insertionOrder;

    fillBackwardFromJacobsthal(insertionOrder, jacobSequence);
    fillRemainingIndices(insertionOrder, pendSize);

    return insertionOrder;
}
