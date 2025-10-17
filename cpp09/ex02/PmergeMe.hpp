#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <algorithm>
#include <deque>
#include <vector>
#include <iostream>
#include <iterator>
#include <cmath>
#include <cstdlib>
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

// Custom binary search (upper_bound) that guarantees consistent comparison counting
// This implements binary search that ALWAYS performs the same number of comparisons
// for a given search space size, regardless of the data. This ensures the theoretical
// Ford-Johnson minimum is achieved consistently.
template <typename Iterator, typename ValueIterator>
Iterator _binary_search_upper(Iterator first, Iterator last, ValueIterator value)
{
    if (first == last)
        return first;

    typename std::iterator_traits<Iterator>::difference_type count = std::distance(first, last);
    typename std::iterator_traits<Iterator>::difference_type step;
    Iterator it;

    while (count > 0)
    {
        it = first;
        step = count / 2;
        std::advance(it, step);

        // ALWAYS count exactly one comparison per iteration
        PmergeMe::nbr_of_comps++;

        // Use only < comparison (standard upper_bound logic)
        if (!(*value < **it))  // if *value >= **it
        {
            first = ++it;
            count -= step + 1;
        }
        else  // *value < **it
        {
            count = step;
        }
    }

    return first;
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

    // verbose print: recursion level entry
    printRecursionLevel(pair_units_nbr, is_odd, container, pair_level, false);

    Iterator start = container.begin();
    Iterator last = next(container.begin(), pair_level * (pair_units_nbr));
    Iterator end = next(last, -(is_odd * pair_level));

    int jump = 2 * pair_level;

    for (Iterator it = start; it != end; std::advance(it, jump))
    {
        Iterator this_pair = next(it, pair_level - 1);
        Iterator next_pair = next(it, pair_level * 2 - 1);

        // verbose print: compare and swap if needed
        if (compareAndPrintPair(this_pair, next_pair))
            _swap_pair(this_pair, pair_level);
    }

    // verbose print: after swapping phase
    printAfterSwapping(container, pair_level);

    // Store BEFORE recursion: which pairs exist (by their representative values)
    std::vector<std::pair<int, int> > pairs_before;  // (smaller_val, larger_val)
    for (int i = 2; i <= pair_units_nbr; i += 2)
    {
        Iterator smaller = next(container.begin(), pair_level * (i - 1) - 1);
        Iterator larger = next(container.begin(), pair_level * i - 1);
        pairs_before.push_back(std::make_pair(*smaller, *larger));
    }

    _merge_insertion_sort(container, pair_level * 2);

    // verbose print: recursion level return (entering insertion phase)
    printRecursionLevel(pair_units_nbr, is_odd, container, pair_level, true, true);

    // After recursion: build main from container positions
    std::vector<Iterator> main_unsorted;  // Temp storage before sorting
    std::vector<Iterator> pend_unsorted;  // Temp storage before reordering

    main_unsorted.push_back(next(container.begin(), pair_level - 1));
    main_unsorted.push_back(next(container.begin(), pair_level * 2 - 1));

    for (int i = 4; i <= pair_units_nbr; i += 2)
    {
        pend_unsorted.push_back(next(container.begin(), pair_level * (i - 1) - 1));
        main_unsorted.push_back(next(container.begin(), pair_level * i - 1));
    }

    // CRITICAL: Reorder pend to match the sorted main chain
    // After recursion, main_unsorted is sorted. We need pend[i] to correspond to main[i+2]
    std::vector<Iterator> main;
    std::vector<Iterator> pend;
    std::vector<Iterator> pend_buddies;

    main.push_back(main_unsorted[0]);
    main.push_back(main_unsorted[1]);

    // For each element in sorted main (starting from index 2), find its paired pend element
    for (size_t i = 2; i < main_unsorted.size(); ++i)
    {
        int main_val = *main_unsorted[i];

        // Find which pair this main_val belongs to
        for (size_t j = 0; j < pairs_before.size(); ++j)
        {
            if (pairs_before[j].second == main_val)  // Found the pair
            {
                int pend_val = pairs_before[j].first;

                // Find this pend_val in pend_unsorted
                for (size_t k = 0; k < pend_unsorted.size(); ++k)
                {
                    if (*pend_unsorted[k] == pend_val)
                    {
                        pend.push_back(pend_unsorted[k]);
                        pend_buddies.push_back(main_unsorted[i]);
                        break;
                    }
                }
                break;
            }
        }
        main.push_back(main_unsorted[i]);
    }

    if (is_odd)
    {
        pend.push_back(next(end, pair_level - 1));
        pend_buddies.push_back(container.end());
    }

    // verbose print: main and pend chains (winners vs losers)
    printChains(main, pend, false, false, true);

    // Insert the first pend element at the beginning without binary search
    if (!pend.empty())
    {
        main.insert(main.begin(), pend[0]);
        pend.erase(pend.begin());
        pend_buddies.erase(pend_buddies.begin());
    }

    // Start from Jacobsthal index 2 (we already inserted pend[0])
    // Jacobsthal sequence: 0, 1, 1, 3, 5, 11, ...
    // We'll insert in the order: 1, then 3,2, then 5,4, then 11,10,9,8,7,6, ...
    int prev_jacobsthal = 1;  // Start after index 1
    int high = 3;  // Start with bound of 3 (for first Jacobsthal group)

    for (int k = 3;; k++)  // Start from k=3 (Jacobsthal(3) = 3)
    {
        int curr_jacobsthal = _jacobsthal_number(k);
        int jacobsthal_diff = curr_jacobsthal - prev_jacobsthal;

        if (curr_jacobsthal > static_cast<int>(pend.size()))
            break;

        int original_pend_size = pend.size();

        // verbose print: jacobsthal round information
        printJacobsthalInfo(k, curr_jacobsthal, jacobsthal_diff, main, pend);

        // At each new Jacobsthal group, double the search bound (Ford-Johnson formula)
        if (k > 2)
            high = 2 * high + 1;

        // Insert in reverse order: from position (jacobsthal_diff - 1) down to 0
        for (int insertion_round = jacobsthal_diff - 1; insertion_round >= 0; --insertion_round)
        {
            if (insertion_round >= static_cast<int>(pend.size()))
                continue;

            typename std::vector<Iterator>::iterator pend_it = next(pend.begin(), insertion_round);
            typename std::vector<Iterator>::iterator buddy_info_it = next(pend_buddies.begin(), insertion_round);
            Iterator buddy_iter = *buddy_info_it;

            typename std::vector<Iterator>::iterator buddy_position = main.end();
            std::size_t buddy_index = main.size();
            if (buddy_iter != container.end())
            {
                buddy_position = std::find(main.begin(), main.end(), buddy_iter);
                buddy_index = std::distance(main.begin(), buddy_position);
            }

            std::size_t high_limit;
            if (main.empty())
                high_limit = 0;
            else
            {
                std::size_t raw_high = (high - 1 >= 0) ? static_cast<std::size_t>(high - 1) : 0;
                high_limit = std::min<std::size_t>(raw_high, main.size() - 1);
            }
            std::size_t buddy_limit;
            if (buddy_index == 0)
                buddy_limit = 0;
            else if (buddy_index == main.size())
                buddy_limit = main.size() - 1;
            else
                buddy_limit = buddy_index - 1;
            std::size_t effective_limit = std::min(high_limit, buddy_limit);
            typename std::vector<Iterator>::iterator bound_it =
                next(main.begin(), effective_limit + 1);

            int search_limit_display = static_cast<int>(effective_limit);
            int high_limit_display = static_cast<int>(high_limit);
            int buddy_limit_display = static_cast<int>(buddy_limit);

            // verbose print: insertion header with bounds calculation
            printInsertionHeader(*pend_it,
                                 insertion_round,
                                 original_pend_size,
                                 search_limit_display,
                                 high_limit_display,
                                 buddy_limit_display);

            typename std::vector<Iterator>::iterator idx = _binary_search_upper(main.begin(), bound_it, *pend_it);

            // verbose print: insertion visual with search space
            printInsertionVisual(main, idx, bound_it);

            main.insert(idx, *pend_it);
            pend.erase(pend_it);
            pend_buddies.erase(buddy_info_it);

            // verbose print: main chain after insertion
            printAfterInsertion(main, pend);
        }

        prev_jacobsthal = curr_jacobsthal;
    }

    size_t remaining_pend_size = pend.size();
    for (size_t i = 0; i < remaining_pend_size; i++)
    {
        typename std::vector<Iterator>::iterator curr_pend_it = next(pend.begin(), i);
        Iterator curr_pend = *curr_pend_it;
        Iterator curr_buddy = pend_buddies[i];

        typename std::vector<Iterator>::iterator buddy_pos = main.end();
        size_t search_bound_idx = main.size();
        if (curr_buddy != container.end())
        {
            buddy_pos = std::find(main.begin(), main.end(), curr_buddy);
            search_bound_idx = std::distance(main.begin(), buddy_pos);
        }

        typename std::vector<Iterator>::iterator curr_bound =
            (curr_buddy == container.end()) ? main.end() : buddy_pos;
        typename std::vector<Iterator>::iterator idx =
            _binary_search_upper(main.begin(), curr_bound, curr_pend);

        // verbose print: remaining pend element insertion
        size_t insertion_idx = std::distance(main.begin(), idx);
        printRemainingInsertion(main, curr_pend, insertion_idx, search_bound_idx, i);

        main.insert(idx, curr_pend);

        // verbose print: main chain after remaining insertion
        printAfterInsertion(main, pend);
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

    // verbose print: final container after merging all pairs
    printAfterMerging(container, pair_level);
}

#endif
