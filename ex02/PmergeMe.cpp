#include "PmergeMe.hpp"
#include <cstdlib>
#include <climits>
#include <utility>
#include <algorithm>

PmergeMe::PmergeMe()
{

}
PmergeMe::PmergeMe(const PmergeMe& copy)
{
    (void) copy;
}
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    (void) other;
    return *this;
}
PmergeMe::~PmergeMe()
{

}

bool PmergeMe::isValidArg(int ac, char **av)
{
    for (int i = 1; i < ac; i++)
    {
        std::string arg = av[i];
        // if (arg.size() == 1 && arg[0] == '0')
        // {
        //     std::cerr << "Error: invlaid character" << std::endl;
        //     return false;
        // }
        // size_t not_valid = arg.find_first_not_of("0123456789+ ");
        // if (not_valid != std::string::npos)
        // {
        //     std::cerr << "Error: invlaid character" << std::endl;
        //     return false;
        // }
        char *end;
        long value = std::strtol(arg.c_str(), &end, 10);
        if (*end != '\0' || value < 0 || value > INT_MAX)
        {
            std::cerr << "Error" << std::endl;
            return false;
        }
        _input.push_back(static_cast<int>(value));
    }
    std::cout << "Before: ";
    std::vector<int>::iterator it = _input.begin();
    for(; it != _input.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
    return true;
}

bool comparePairs(const std::pair<int, int>& a,
                  const std::pair<int, int>& b)
{
    return a.first < b.first;
}

int Jacobsthal(int n)
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);
	return (Jacobsthal(n - 1) + 2 * Jacobsthal(n - 2));
}

std::vector<int> PmergeMe::jacobsthalOrder(int pendSize)
{
    std::vector<int> order;
    if (pendSize <= 0)
        return order;

    int prev = 1;
    int k = 3;

    while ((int)order.size() < pendSize)
    {
        int curr = Jacobsthal(k);
        int upper = std::min(curr, pendSize + 1);
        int lower = prev + 1;

        for (int idx = upper; idx >= lower; idx--)
        {
            order.push_back(idx);
        }
        prev = curr;
        k++;
    }
    return order;
}

void PmergeMe::insertPend(std::vector<int>& main_chain, std::vector<std::pair<int, int> >& pend)
{
    std::vector<int> order = jacobsthalOrder((int)pend.size());

    for (size_t i = 0; i < order.size(); i++)
    {
        int pendIndex = order[i] - 2;
        int value  = pend[pendIndex].first;
        int leader = pend[pendIndex].second; 

        std::vector<int>::iterator leaderPos =
            std::find(main_chain.begin(), main_chain.end(), leader);
        std::vector<int>::iterator insertPos =
            std::lower_bound(main_chain.begin(), leaderPos, value);
        
        main_chain.insert(insertPos, value);
    }
}

void PmergeMe::make_pairs()
{
    int struggler = -1;
    bool has_struggler = false;
    if (_input.size() % 2 != 0)
    {
        has_struggler = true;
        struggler = _input.back();
        _input.pop_back();
    }
    std::vector<std::pair<int, int> > pairs;
    typedef std::vector<int>::iterator it_t;
    for (it_t it = _input.begin(); it != _input.end(); it += 2)
    {
        pairs.push_back(std::make_pair(*it, *(it+1)));
    }
    typedef std::vector<std::pair<int, int> >::iterator pair_it;

    for(pair_it it = pairs.begin(); it != pairs.end(); it++)
    {
        if (it->first < it->second)
        {
            std::swap(it->first, it->second);
        }
    }
    
    std::sort(pairs.begin(), pairs.end(), comparePairs);

    std::vector<int> main_chain;
    std::vector<std::pair<int, int> > pend;

    main_chain.push_back(pairs.at(0).second);
    for(unsigned long i = 0; i < pairs.size(); i++)
    {
        main_chain.push_back(pairs.at(i).first);
        if (i != 0)
        {
            pend.push_back(std::make_pair(pairs.at(i).second, pairs.at(i).first));
        }
    }

    insertPend(main_chain, pend);

    if (has_struggler)
    {
        std::vector<int>::iterator pos =
            std::lower_bound(main_chain.begin(), main_chain.end(), struggler);
        main_chain.insert(pos, struggler);
    }

    std::cout << "Final sorted: ";
    for (std::vector<int>::iterator it = main_chain.begin(); it != main_chain.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}



//========================std::deque==================================
std::deque<int> PmergeMe::jacobsthalOrder_deque(int pendSize)
{
    std::deque<int> order;
    if (pendSize <= 0)
        return order;

    int prev = 1;
    int k = 3;

    while ((int)order.size() < pendSize)
    {
        int curr = Jacobsthal(k);
        int upper = std::min(curr, pendSize + 1);
        int lower = prev + 1;

        for (int idx = upper; idx >= lower; idx--)
        {
            order.push_back(idx);
        }
        prev = curr;
        k++;
    }
    return order;
}

void PmergeMe::insertPend_deque(std::deque<int>& main_chain, std::deque<std::pair<int, int> >& pend)
{
    std::deque<int> order = jacobsthalOrder_deque((int)pend.size());

    for (size_t i = 0; i < order.size(); i++)
    {
        int pendIndex = order[i] - 2;
        int value  = pend[pendIndex].first;
        int leader = pend[pendIndex].second; 

        std::deque<int>::iterator leaderPos =
            std::find(main_chain.begin(), main_chain.end(), leader);
        std::deque<int>::iterator insertPos =
            std::lower_bound(main_chain.begin(), leaderPos, value);
        
        main_chain.insert(insertPos, value);
    }
}

void PmergeMe::make_pairs_deque()
{
    _deque_in.assign(_input.begin(), _input.end() + 1);

    int struggler = -1;
    bool has_struggler = false;
    if (_deque_in.size() % 2 != 0)
    {
        has_struggler = true;
        struggler = _deque_in.back();
        _deque_in.pop_back();
    }
    std::deque<std::pair<int, int> > pairs;
    typedef std::deque<int>::iterator it_t;
    for (it_t it = _deque_in.begin(); it != _deque_in.end(); it += 2)
    {
        pairs.push_back(std::make_pair(*it, *(it+1)));
    }
    typedef std::deque<std::pair<int, int> >::iterator pair_it;

    for(pair_it it = pairs.begin(); it != pairs.end(); it++)
    {
        if (it->first < it->second)
        {
            std::swap(it->first, it->second);
        }
    }
    
    std::sort(pairs.begin(), pairs.end(), comparePairs);

    std::deque<int> main_chain;
    std::deque<std::pair<int, int> > pend;

    main_chain.push_back(pairs.at(0).second);
    for(unsigned long i = 0; i < pairs.size(); i++)
    {
        main_chain.push_back(pairs.at(i).first);
        if (i != 0)
        {
            pend.push_back(std::make_pair(pairs.at(i).second, pairs.at(i).first));
        }
    }

    insertPend_deque(main_chain, pend);

    if (has_struggler)
    {
        std::deque<int>::iterator pos =
            std::lower_bound(main_chain.begin(), main_chain.end(), struggler);
        main_chain.insert(pos, struggler);
    }

    std::cout << "Final sorted: ";
    for (std::deque<int>::iterator it = main_chain.begin(); it != main_chain.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}