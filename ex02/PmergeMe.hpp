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

    std::vector<int> jacobsthalOrderVector(int pendSize);
    void insertPendVector(std::vector<int> &main_chain, std::vector<std::pair<int, int> > &pend);
    void makePairsVector(std::vector<std::pair<int, int> > &pairs, int &struggler, bool &has_struggler);
    void sortPairsVector(std::vector<std::pair<int, int> > &pairs);
    void buildMainChainVector(const std::vector<std::pair<int, int> > &pairs, std::vector<int> &main_chain, std::vector<std::pair<int, int> > &pend);
    void insertStrugglerVector(std::vector<int> &main_chain, int struggler);

    std::deque<int> jacobsthalOrderDeque(int pendSize);
    void insertPendDeque(std::deque<int> &main_chain, std::deque<std::pair<int, int> > &pend);
    void makePairsDeque(std::deque<std::pair<int, int> > &pairs, int &struggler, bool &has_struggler);
    void sortPairsDeque(std::deque<std::pair<int, int> > &pairs);
    void buildMainChainDeque(const std::deque<std::pair<int, int> > &pairs, std::deque<int> &main_chain, std::deque<std::pair<int, int> > &pend);
    void insertStrugglerDeque(std::deque<int> &main_chain, int struggler);

public:
    PmergeMe();
    PmergeMe(const PmergeMe &copy);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();

    bool isValidArg(int ac, char **av);
    double sortVector(std::vector<int> &result);
    double sortDeque(std::deque<int> &result);
    const std::vector<int> &getInput() const;
};

#endif