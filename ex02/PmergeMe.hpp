#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <vector>

class PmergeMe
{
    private:
        std::vector<int> _input;
    public:
        PmergeMe();
        PmergeMe(const PmergeMe& copy);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        bool isValidArg(int ac, char **av);
    
};

#endif