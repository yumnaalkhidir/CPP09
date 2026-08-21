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
        if (*end != '\0' || value <= 0 || value > INT_MAX)
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

void PmergeMe::make_pairs()
{
    if (_input.size() % 2 != 0)
    {
        int struggler;
        struggler = _input.back();
        _input.pop_back();
        std::cout << "Struggler: " << struggler << std::endl;
    }

    std::vector<std::pair<int, int> > pairs;
    typedef std::vector<int>::iterator it_t;
    for (it_t it = _input.begin(); it != _input.end(); it += 2)
    {
        pairs.push_back(std::make_pair(*it, *(it+1)));
    }
    std::cout << "Pairs created" << std::endl;
    typedef std::vector<std::pair<int, int> >::iterator pair_it;
    std::cout << "Each pair has the larger element as first" << std::endl;
    for(pair_it it = pairs.begin(); it != pairs.end(); it++)
    {
        if (it->first < it->second)
        {
            std::swap(it->first, it->second);
        }
        std::cout << it->first << " " << it->second << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Pairs are sorted in accending order according to the first element" << std::endl;
    std::sort(pairs.begin(), pairs.end(), comparePairs);
    for(pair_it it = pairs.begin(); it != pairs.end(); it++)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }


}