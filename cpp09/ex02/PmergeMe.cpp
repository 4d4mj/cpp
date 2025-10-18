#include "PmergeMe.hpp"
#include "vector/VectorSort.hpp"
#include "deque/DequeSort.hpp"

// Initialize static member
int PmergeMe::nbrOfComparisons = 0;

// Constructors
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &pm)
{
    (void)pm;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &pm)
{
    (void)pm;
    return *this;
}

PmergeMe::~PmergeMe() {}

// Sort vector using Ford-Johnson algorithm
void PmergeMe::sortVector(std::vector<int> &vec)
{
    fordJohnsonSortVector(vec, nbrOfComparisons);
}

// Sort deque using Ford-Johnson algorithm
void PmergeMe::sortDeque(std::deque<int> &deq)
{
    fordJohnsonSortDeque(deq, nbrOfComparisons);
}
