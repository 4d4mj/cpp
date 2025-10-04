#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <algorithm>
#include <deque>
#include <vector>
#include <iostream>
#include <iterator>
#include <cmath>
#include <cstdlib>
#include "PrintUtils.hpp"

extern bool g_verbose;

class PmergeMe
{
public:
    PmergeMe();
    PmergeMe(const PmergeMe &pm);
    PmergeMe &operator=(const PmergeMe &pm);
    ~PmergeMe();

    void sort_vec(std::vector<int> &vec);
    void sort_deque(std::deque<int> &deque);

    static int nbr_of_comps;

private:
    template <typename T>
    void _merge_insertion_sort(T &container, int pair_level);
    template <typename T>
    void _swap_pair(T it, int pair_level);
};

long _jacobsthal_number(long n);

// Generic comparator that counts comparisons.
template <typename T>
bool _comp(T lv, T rv)
{
    PmergeMe::nbr_of_comps++;
    return *lv < *rv;
}

template <typename T>
T next(T it, int steps)
{
    std::advance(it, steps);
    return it;
}

template <typename T>
void PmergeMe::_swap_pair(T it, int pair_level)
{
    T start = next(it, -pair_level + 1);
    T end = next(start, pair_level);
    while (start != end)
    {
        std::iter_swap(start, next(start, pair_level));
        start++;
    }
}

template <typename T>
void PmergeMe::_merge_insertion_sort(T &container, int pair_level)
{
    typedef typename T::iterator Iterator;

    int pair_units_nbr = container.size() / pair_level;
    if (pair_units_nbr < 2)
        return;

    bool is_odd = (pair_units_nbr % 2 == 1);

    // verbose print
    printRecursionLevel(pair_units_nbr, is_odd, container, pair_level, false);

    Iterator start = container.begin();
    Iterator last = next(container.begin(), pair_level * (pair_units_nbr));
    Iterator end = next(last, -(is_odd * pair_level));

    int jump = 2 * pair_level;

    for (Iterator it = start; it != end; std::advance(it, jump))
    {
        Iterator this_pair = next(it, pair_level - 1);
        Iterator next_pair = next(it, pair_level * 2 - 1);

        // verbose print & compare
        if (compareAndPrintPair(this_pair, next_pair))
            _swap_pair(this_pair, pair_level);
    }

    // verbose print
    printContainerAsGroups(container, pair_level);

    _merge_insertion_sort(container, pair_level * 2);

    // verbose print
    printRecursionLevel(pair_units_nbr, is_odd, container, pair_level, true, true);

    std::vector<Iterator> main;
    std::vector<Iterator> pend;

    main.push_back(next(container.begin(), pair_level - 1));
    main.push_back(next(container.begin(), pair_level * 2 - 1));

    for (int i = 4; i <= pair_units_nbr; i += 2)
    {
        pend.push_back(next(container.begin(), pair_level * (i - 1) - 1));
        main.push_back(next(container.begin(), pair_level * i - 1));
    }

    if (is_odd)
        pend.push_back(next(end, pair_level - 1));

    // verbose print
    printChains(main, pend, false, false, true);

    int prev_jacobsthal = _jacobsthal_number(1);
    int inserted_numbers = 0;

    for (int k = 2;; k++)
    {
        int curr_jacobsthal = _jacobsthal_number(k);
        int jacobsthal_diff = curr_jacobsthal - prev_jacobsthal;
        int offset = 0;
        if (jacobsthal_diff > static_cast<int>(pend.size()))
        break;
        int nbr_of_times = jacobsthal_diff;
        typename std::vector<Iterator>::iterator pend_it = next(pend.begin(), jacobsthal_diff - 1);
        typename std::vector<Iterator>::iterator bound_it =
        next(main.begin(), curr_jacobsthal + inserted_numbers);

        // verbose print
        printJacobsthalInfo(k, curr_jacobsthal, jacobsthal_diff, main, pend);

        while (nbr_of_times)
        {
            typename std::vector<Iterator>::iterator idx = std::upper_bound(main.begin(), bound_it, *pend_it, _comp<Iterator>);

            // verbose print
            printInsertionVisual(main, idx);
            typename std::vector<Iterator>::iterator inserted = main.insert(idx, *pend_it);
            nbr_of_times--;
            pend_it = pend.erase(pend_it);
            std::advance(pend_it, -1);
            offset += (inserted - main.begin()) == (curr_jacobsthal + inserted_numbers);
            bound_it = next(main.begin(), curr_jacobsthal + inserted_numbers - offset);

            // verbose print
            printChains(main, pend, true);
        }
        prev_jacobsthal = curr_jacobsthal;
        inserted_numbers += jacobsthal_diff;
        offset = 0;
    }

    for (size_t i = 0; i < pend.size(); i++)
    {
        typename std::vector<Iterator>::iterator curr_pend = next(pend.begin(), i);
        typename std::vector<Iterator>::iterator curr_bound =
            next(main.begin(), main.size() - pend.size() + i + is_odd);
        typename std::vector<Iterator>::iterator idx =
            std::upper_bound(main.begin(), curr_bound, *curr_pend, _comp<Iterator>);

        // verbose print

        main.insert(idx, *curr_pend);
        printRemainingInsertion(main, *curr_pend, std::distance(main.begin(), idx));
    }

    std::vector<int> tempCopy;
    tempCopy.reserve(container.size());
    {
        typename std::vector<Iterator>::iterator it;
        for (it = main.begin(); it != main.end(); ++it)
        {
            for (int i = 0; i < pair_level; i++)
            {
                Iterator pair_start = *it;
                std::advance(pair_start, -pair_level + i + 1);
                tempCopy.push_back(*pair_start);
            }
        }
    }

    Iterator container_it = container.begin();
    typename std::vector<int>::iterator tempCopy_it = tempCopy.begin();
    while (tempCopy_it != tempCopy.end())
    {
        *container_it = *tempCopy_it;
        ++container_it;
        ++tempCopy_it;
    }
#ifdef VERBOSE
    DEBUG_PRINT("Container after merging: ");
    printContainerAsGroups(container, pair_level, false);
#endif
}

#endif
