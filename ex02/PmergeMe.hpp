#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <vector>

class PmergeMe
{
    private:
        std::vector<int> _input;
        std::vector<int> _vec_algo;
    public:
        PmergeMe();
        PmergeMe(const PmergeMe& copy);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        bool isValidArg(int ac, char **av);
        void make_pairs();

};

#endif