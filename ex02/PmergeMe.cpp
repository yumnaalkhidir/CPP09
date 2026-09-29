#include "PmergeMe.hpp"
#include <cstdlib>
#include <climits>
#include <utility>
#include <algorithm>
#include <ctime>


PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
    (void)copy;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    (void)other;
    return *this;
}

PmergeMe::~PmergeMe()
{
}

const std::vector<int>& PmergeMe::getInput() const
{
    return _input;
}

bool PmergeMe::isValidArg(int ac, char **av)
{
    for (int i = 1; i < ac; i++)
    {
        std::string arg = av[i];

        char *end;
        long value = std::strtol(arg.c_str(), &end, 10);
        if (*end != '\0' || value < 0 || value > INT_MAX)
        {
            std::cerr << "Error" << std::endl;
            return false;
        }
        _input.push_back(static_cast<int>(value));
    }
    return true;
}

int PmergeMe::Jacobsthal(int n)
{
    if (n == 0)
        return (0);
    if (n == 1)
        return (1);
    return (Jacobsthal(n - 1) + 2 * Jacobsthal(n - 2));
}

std::vector<int> PmergeMe::jacobsthalOrderVector(int pendSize)
{
    std::vector<int> order;

    if (pendSize <= 0)
        return order;

    int prev = 1;
    int j_n = 3;

    while ((int)order.size() < pendSize)
    {
        int curr = Jacobsthal(j_n);
        int upper = std::min(curr, pendSize + 1);
        int lower = prev + 1;

        for (int idx = upper; idx >= lower; idx--)
        {
            order.push_back(idx);
        }
        prev = curr;
        j_n++;
    }
    return order;
}

void PmergeMe::insertPendVector(std::vector<int> &main_chain,
    std::vector<std::pair<int, int> > &pend)
{
    std::vector<int> order = jacobsthalOrderVector((int)pend.size());

    for (size_t i = 0; i < order.size(); i++)
    {
        int pendIndex = order[i] - 2;
        int value = pend[pendIndex].first;
        int leader = pend[pendIndex].second;

        std::vector<int>::iterator leaderPos =
            std::find(main_chain.begin(), main_chain.end(), leader);
        std::vector<int>::iterator insertPos =
            std::lower_bound(main_chain.begin(), leaderPos, value);

        main_chain.insert(insertPos, value);
    }
}

void PmergeMe::insertStrugglerVector(std::vector<int> &main_chain,
    int struggler)
{
    std::vector<int>::iterator pos =
        std::lower_bound(main_chain.begin(), main_chain.end(), struggler);
    main_chain.insert(pos, struggler);
}

void PmergeMe::makePairsVector(const std::vector<int> &input,
    std::vector<std::pair<int, int> > &pairs,
    int &struggler, bool &has_struggler)
{
    std::vector<int> values = input;

    if (values.size() % 2 != 0)
    {
        has_struggler = true;
        struggler = values.back();
        values.pop_back();
    }

    for (std::vector<int>::iterator it = values.begin();
         it != values.end();
         it += 2)
    {
        int first = *it;
        int second = *(it + 1);

        if (first < second)
            std::swap(first, second);

        pairs.push_back(std::make_pair(first, second));
    }
}

void PmergeMe::mergeInsertSortVector(std::vector<int> &arr)
{
    if (arr.size() <= 1)
        return;

    std::vector<std::pair<int, int> > pairs;

    int struggler = -1;
    bool has_struggler = false;

    makePairsVector(arr, pairs, struggler, has_struggler);
   
    std::vector<int> larger;

    for (size_t i = 0; i < pairs.size(); i++)
        larger.push_back(pairs[i].first);

    mergeInsertSortVector(larger);

    std::vector<std::pair<int, int> > sortedPairs;
    std::vector<bool> used(pairs.size(), false);

    for (size_t i = 0; i < larger.size(); i++)
    {
        for (size_t j = 0; j < pairs.size(); j++)
        {
            if (!used[j] && pairs[j].first == larger[i])
            {
                sortedPairs.push_back(pairs[j]);
                used[j] = true;
                break;
            }
        }
    }

    std::vector<int> main_chain;
    std::vector<std::pair<int, int> > pend;
    main_chain.push_back(sortedPairs[0].second);

    for (size_t i = 0; i < sortedPairs.size(); i++)
    {
        main_chain.push_back(sortedPairs[i].first);

        if (i != 0)
        {
            pend.push_back(
                std::make_pair(
                    sortedPairs[i].second,
                    sortedPairs[i].first
                )
            );
        }
    }

    insertPendVector(main_chain, pend);

    if (has_struggler)
        insertStrugglerVector(main_chain, struggler);

    arr = main_chain;
}

double PmergeMe::vector(std::vector<int> &result)
{
    std::vector<int> values = _input;

    std::clock_t start = clock();

    mergeInsertSortVector(values);

    std::clock_t end = clock();

    result = values;

    double duration =
        static_cast<double>(end - start)
        / CLOCKS_PER_SEC * 1000000;

    return duration;
}

//===========================DEQUE===============================

std::deque<int> PmergeMe::jacobsthalOrderDeque(int pendSize)
{
    std::deque<int> order;

    if (pendSize <= 0)
        return order;

    int prev = 1;
    int j_n = 3;

    while ((int)order.size() < pendSize)
    {
        int curr = Jacobsthal(j_n);
        int upper = std::min(curr, pendSize + 1);
        int lower = prev + 1;

        for (int idx = upper; idx >= lower; idx--)
        {
            order.push_back(idx);
        }
        prev = curr;
        j_n++;
    }
    return order;
}

void PmergeMe::insertPendDeque(std::deque<int> &main_chain,
    std::deque<std::pair<int, int> > &pend)
{
    std::deque<int> order = jacobsthalOrderDeque((int)pend.size());

    for (size_t i = 0; i < order.size(); i++)
    {
        int pendIndex = order[i] - 2;
        int value = pend[pendIndex].first;
        int leader = pend[pendIndex].second;

        std::deque<int>::iterator leaderPos =
            std::find(main_chain.begin(), main_chain.end(), leader);
        std::deque<int>::iterator insertPos =
            std::lower_bound(main_chain.begin(), leaderPos, value);

        main_chain.insert(insertPos, value);
    }
}

void PmergeMe::insertStrugglerDeque(std::deque<int> &main_chain,
    int struggler)
{
    std::deque<int>::iterator pos =
        std::lower_bound(main_chain.begin(), main_chain.end(), struggler);
    main_chain.insert(pos, struggler);
}

void PmergeMe::makePairsDeque(const std::deque<int> &input,
    std::deque<std::pair<int, int> > &pairs,
    int &struggler, bool &has_struggler)
{
    std::deque<int> values = input;

    if (values.size() % 2 != 0)
    {
        has_struggler = true;
        struggler = values.back();
        values.pop_back();
    }

    for (std::deque<int>::iterator it = values.begin();
         it != values.end();
         it += 2)
    {
        int first = *it;
        int second = *(it + 1);

        if (first < second)
            std::swap(first, second);

        pairs.push_back(std::make_pair(first, second));
    }
}

void PmergeMe::mergeInsertSortDeque(std::deque<int> &arr)
{
    if (arr.size() <= 1)
        return;

    std::deque<std::pair<int, int> > pairs;

    int struggler = -1;
    bool has_struggler = false;

    makePairsDeque(arr, pairs, struggler, has_struggler);
   
    std::deque<int> larger;

    for (size_t i = 0; i < pairs.size(); i++)
        larger.push_back(pairs[i].first);

    mergeInsertSortDeque(larger);

    std::deque<std::pair<int, int> > sortedPairs;
    std::deque<bool> used(pairs.size(), false);

    for (size_t i = 0; i < larger.size(); i++)
    {
        for (size_t j = 0; j < pairs.size(); j++)
        {
            if (!used[j] && pairs[j].first == larger[i])
            {
                sortedPairs.push_back(pairs[j]);
                used[j] = true;
                break;
            }
        }
    }

    std::deque<int> main_chain;
    std::deque<std::pair<int, int> > pend;
    main_chain.push_back(sortedPairs[0].second);

    for (size_t i = 0; i < sortedPairs.size(); i++)
    {
        main_chain.push_back(sortedPairs[i].first);

        if (i != 0)
        {
            pend.push_back(
                std::make_pair(
                    sortedPairs[i].second,
                    sortedPairs[i].first
                )
            );
        }
    }

    insertPendDeque(main_chain, pend);

    if (has_struggler)
        insertStrugglerDeque(main_chain, struggler);

    arr = main_chain;
}

double PmergeMe::deque(std::deque<int> &result)
{
    std::deque<int> values(_input.begin(), _input.end());;

    std::clock_t start = clock();

    mergeInsertSortDeque(values);

    std::clock_t end = clock();

    result = values;

    double duration =
        static_cast<double>(end - start)
        / CLOCKS_PER_SEC * 1000000;

    return duration;
}