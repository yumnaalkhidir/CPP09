#include "PmergeMe.hpp"
#include <cstdlib>
#include <climits>

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