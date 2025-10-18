#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <vector>
#include "print/Print.hpp"

extern bool g_verbose;

class PmergeMe
{
public:
    PmergeMe();
    PmergeMe(const PmergeMe &pm);
    PmergeMe &operator=(const PmergeMe &pm);
    ~PmergeMe();

    void sort_vec(std::vector<int> &vec);
    void sort_deque(std::deque<int> &deq);

    static int nbr_of_comps;
};

long _jacobsthal_number(long n);

template <typename T>
bool _comp(T lv, T rv)
{
    PmergeMe::nbr_of_comps++;
    return *lv < *rv;
}

#endif
