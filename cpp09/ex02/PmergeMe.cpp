#include "PmergeMe.hpp"
#include <algorithm>
#include <cstddef>
#include <deque>
#include <vector>

int PmergeMe::nbr_of_comps = 0;

namespace
{
long jacobsthal_internal(long n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    long prev2 = 0;
    long prev1 = 1;
    long curr = 0;
    for (long i = 2; i <= n; ++i)
    {
        curr = prev1 + 2 * prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return curr;
}

template <typename Value>
struct Element
{
    Value value;
    std::size_t index;

    Element() : value(), index(0) {}
    Element(const Value &v, std::size_t idx) : value(v), index(idx) {}
};

template <typename Value>
bool elementGreater(const Element<Value> &lhs, const Element<Value> &rhs)
{
    ++PmergeMe::nbr_of_comps;
    if (lhs.value == rhs.value)
        return lhs.index > rhs.index;
    return lhs.value > rhs.value;
}

std::vector<int> jacobthalIndices(std::size_t size)
{
    std::vector<int> jacobSequence;
    int jacobIndex = 3;
    while (true)
    {
        long value = jacobsthal_internal(jacobIndex);
        if (value > static_cast<long>(size))
            break;
        jacobSequence.push_back(static_cast<int>(value));
        jacobIndex++;
    }
    return jacobSequence;
}

void editIndices(std::vector<int> &jacob, std::size_t pend_size)
{
    std::vector<int> temp;
    std::vector<int> pushed;

    for (std::vector<int>::iterator it = jacob.begin(); it != jacob.end(); ++it)
    {
        int x = *it;
        while (x > 1)
        {
            if (std::find(pushed.begin(), pushed.end(), x) == pushed.end())
            {
                temp.push_back(x);
                pushed.push_back(x);
            }
            else
            {
                break;
            }
            --x;
        }
    }

    if (temp.size() == pend_size)
    {
        jacob = temp;
    }
    else
    {
        int x = static_cast<int>(pend_size);
        while (temp.size() < pend_size)
        {
            if (std::find(pushed.begin(), pushed.end(), x) == pushed.end())
            {
                temp.push_back(x);
                pushed.push_back(x);
            }
            else
            {
                break;
            }
            --x;
        }
        jacob = temp;
    }
}

template <typename Value>
int binarySearch(const std::vector<Element<Value> > &main,
                 const Element<Value> &pend,
                 int high)
{
    if (main.empty())
        return 0;

    if (high >= static_cast<int>(main.size()))
        high = static_cast<int>(main.size()) - 1;

    int low = 0;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        ++PmergeMe::nbr_of_comps;

        if (main[mid].value == pend.value)
        {
            if (pend.index < main[mid].index)
            {
                high = mid - 1;
            }
            else if (pend.index > main[mid].index)
            {
                low = mid + 1;
            }
            else
            {
                return mid;
            }
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

    if (low < static_cast<int>(main.size()))
    {
        if (pend.value < main[low].value)
            return low;
        if (pend.value == main[low].value && pend.index < main[low].index)
            return low;
    }

    return static_cast<int>(main.size());
}

template <typename Value>
void replaceElements(std::vector<Element<Value> > &main,
                     const std::vector<Element<Value> > &pend,
                     const std::vector<int> &jacob)
{
    if (pend.empty())
        return;

    int high = 3;
    main.insert(main.begin(), pend[0]);

    for (std::vector<int>::const_iterator it = jacob.begin(); it != jacob.end(); ++it)
    {
        if (it != jacob.begin() && *it > *(it - 1))
            high = 2 * high + 1;

        if (*it <= static_cast<int>(pend.size()) && *it != 1)
        {
            int index = binarySearch(main, pend[*it - 1], high - 1);
            if (index != -1)
                main.insert(main.begin() + index, pend[*it - 1]);
        }
    }
}

template <typename Value>
void insertSort(std::vector<Element<Value> > &main,
                const std::vector<Element<Value> > &pend)
{
    if (pend.empty())
        return;

    std::vector<int> jacob = jacobthalIndices(pend.size());
    editIndices(jacob, pend.size());
    replaceElements(main, pend, jacob);
}

template <typename Value>
std::vector<Element<Value> > fordJohnsonLoop(std::vector<Element<Value> > data)
{
    typedef Element<Value> Elem;

    if (data.empty())
        return std::vector<Elem>();
    if (data.size() == 1)
        return data;
    if (data.size() == 2)
    {
        std::vector<Elem> result = data;
        if (elementGreater(result[0], result[1]))
            std::swap(result[0], result[1]);
        return result;
    }

    bool is_odd = (data.size() % 2 == 1);
    std::vector<Elem> main;
    std::vector<Elem> pend;
    main.reserve(data.size() / 2 + 1);
    pend.reserve(data.size() / 2 + 1);

    for (std::size_t i = 0; i + 1 < data.size(); i += 2)
    {
        if (elementGreater(data[i], data[i + 1]))
        {
            main.push_back(data[i]);
            pend.push_back(data[i + 1]);
        }
        else
        {
            pend.push_back(data[i]);
            main.push_back(data[i + 1]);
        }
    }

    if (is_odd)
        pend.push_back(data.back());

    std::vector<Elem> new_main = fordJohnsonLoop(main);

    std::vector<Elem> new_pend(new_main.size());
    for (std::size_t i = 0; i < new_main.size(); ++i)
    {
        for (std::size_t j = 0; j < main.size(); ++j)
        {
            if (main[j].index == new_main[i].index)
            {
                new_pend[i] = pend[j];
                break;
            }
        }
    }

    if (is_odd)
        new_pend.push_back(pend.back());

    insertSort(new_main, new_pend);

    return new_main;
}

template <typename Container>
void fordJohnsonSort(Container &container)
{
    if (container.size() <= 1)
        return;

    typedef typename Container::value_type Value;
    typedef Element<Value> Elem;

    std::vector<Elem> data;
    data.reserve(container.size());
    std::size_t idx = 0;
    for (typename Container::iterator it = container.begin(); it != container.end(); ++it, ++idx)
        data.push_back(Elem(*it, idx));

    std::vector<Elem> sorted = fordJohnsonLoop(data);

    typename Container::iterator out = container.begin();
    for (typename std::vector<Elem>::iterator it = sorted.begin(); it != sorted.end(); ++it, ++out)
        *out = it->value;
}
} // namespace

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &pm) { (void)pm; }
PmergeMe &PmergeMe::operator=(const PmergeMe &pm)
{
    (void)pm;
    return *this;
}
PmergeMe::~PmergeMe() {}

long _jacobsthal_number(long n) { return jacobsthal_internal(n); }

void PmergeMe::sort_vec(std::vector<int> &vec) { fordJohnsonSort(vec); }

void PmergeMe::sort_deque(std::deque<int> &deq) { fordJohnsonSort(deq); }
