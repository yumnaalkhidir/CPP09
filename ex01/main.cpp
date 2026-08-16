#include "RPN.hpp"


int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Error: wrong number of arguments" << std::endl;
        return 1;
    }
    RPN rpn;
    if (!rpn.isValidArg(av[1]))
        return 1;
    rpn.calculate(av[1]);
}