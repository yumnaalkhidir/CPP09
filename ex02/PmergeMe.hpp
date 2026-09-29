#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <vector>
#include <deque>
class PmergeMe
{
private:
    std::vector<int> _input;
    int Jacobsthal(int n);

    std::vector<int> jacobsthalOrderVector(int pendSize);
    void insertPendVector(std::vector<int> &main_chain, std::vector<std::pair<int, int> > &pend);
    void insertStrugglerVector(std::vector<int> &main_chain, int struggler);
    void makePairsVector(const std::vector<int> &input, std::vector<std::pair<int, int> > &pairs, int &struggler, bool &has_struggler);
    void buildMainChainVector(const std::vector<std::pair<int, int> > &pairs, std::vector<int> &main_chain, std::vector<std::pair<int, int> > &pend);
    void mergeInsertSortVector(std::vector<int> &arr);

    std::deque<int> jacobsthalOrderDeque(int pendSize);
    void insertPendDeque(std::deque<int> &main_chain, std::deque<std::pair<int, int> > &pend);
    void insertStrugglerDeque(std::deque<int> &main_chain, int struggler);
    void makePairsDeque(const std::deque<int> &input, std::deque<std::pair<int, int> > &pairs, int &struggler, bool &has_struggler);
    void buildMainChainDeque(const std::deque<std::pair<int, int> > &pairs, std::deque<int> &main_chain, std::deque<std::pair<int, int> > &pend);
    void mergeInsertSortDeque(std::deque<int> &arr);

public:
    PmergeMe();
    PmergeMe(const PmergeMe &copy);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();

    bool isValidArg(int ac, char **av);
    double vector(std::vector<int> &result);
    double deque(std::deque<int> &result);
    const std::vector<int> &getInput() const;
};

#endif