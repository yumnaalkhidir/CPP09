#include "PmergeMe.hpp"
#include <cctype>

int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "Error: too few arguments" << std::endl;
        return 1;
    }

    PmergeMe pmerge;
    if (!pmerge.isValidArg(ac, av))
        return 1;
   
    std::vector<int> input = pmerge.getInput();

    std::cout << "Before: ";
    for (std::vector<int>::iterator it = input.begin(); it != input.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::vector<int> vectorResult;
    
    double vecTime = pmerge.vector(vectorResult);

    std::cout << "After: ";
    for (std::vector<int>::iterator it = vectorResult.begin(); it != vectorResult.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << vectorResult.size() << 
    " elements with std::vector : " << vecTime << " us" << std::endl;
    
    std::deque<int> dequeResult;
    
    double deqTime = pmerge.deque(dequeResult);

    std::cout << "Time to process a range of " << dequeResult.size() << 
    " elements with std::deque : " << deqTime << " us" << std::endl;
}