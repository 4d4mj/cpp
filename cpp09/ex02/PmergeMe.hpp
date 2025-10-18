#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <vector>

class PmergeMe
{
public:
    PmergeMe();
    PmergeMe(const PmergeMe &pm);
    PmergeMe &operator=(const PmergeMe &pm);
    ~PmergeMe();

    // Sort a vector using Ford-Johnson algorithm
    void sortVector(std::vector<int> &vec);

    // Sort a deque using Ford-Johnson algorithm
    void sortDeque(std::deque<int> &deq);

    // Static comparison counter
    static int nbrOfComparisons;
};

#endif
