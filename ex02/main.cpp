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
    pmerge.make_pairs();
}