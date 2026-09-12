#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <vector>
#include <deque>
class PmergeMe
{
    private:
        std::vector<int> _input;
        std::deque<int> _deque_in;
    public:
        PmergeMe();
        PmergeMe(const PmergeMe& copy);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        bool isValidArg(int ac, char **av);
        void make_pairs();
        void insertPend(std::vector<int>& main_chain, std::vector<std::pair<int, int> >& pend);
        std::vector<int> jacobsthalOrder(int pendSize);
        void make_pairs_deque();
        void insertPend_deque(std::deque<int>& main_chain, std::deque<std::pair<int, int> >& pend);
        std::deque<int> jacobsthalOrder_deque(int pendSize);


};

#endif