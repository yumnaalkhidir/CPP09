#include "RPN.hpp"

RPN::RPN()
{}

RPN::RPN(const RPN& copy) : _numbers(copy._numbers)
{}

RPN& RPN::operator=(const RPN& copy)
{
    if (this != &copy)
        _numbers = copy._numbers;
    return *this;
}

RPN::~RPN()
{}

bool RPN::isValidArg(std::string arg) const
{
    size_t not_valid = arg.find_first_not_of("0123456789+-*/ ");
    if (not_valid != std::string::npos)
    {
        std::cout << "Error: invlaid character" << std::endl;
        return false;
    }
    return true;
}
int RPN::performOp(int first, int second, char op) const
{
    if (op == '+')
        return first + second;
    else if (op == '-')
        return first - second;
    else if (op == '*')
        return first * second;
    else
        return first / second;
}
void RPN::calculate(const std::string &expression)
{
    for (size_t i = 0; i < expression.size(); i++)
    {
        char token = expression[i];
        if (token == ' ')
            continue;
        
        if(std::isdigit(token))
        {
            if (i + 1 < expression.size() && std::isdigit(expression[i + 1]))
            {
                std::cout << "Error: Value greater than 9" << std::endl;
                return ;
            }
            _numbers.push(token - '0');
        }
        else if (token == '+' || token == '-' || token == '*' || token == '/')
        {
            if (_numbers.size() < 2)
            {
                std::cerr << "Error: too few operands" << std::endl;
                return ;
            }
            int second = _numbers.top();
            _numbers.pop();
            int first = _numbers.top();
            _numbers.pop();

            if (second == 0 && token == '/')
            {
                std::cerr << "Error: can't divide by zero" << std::endl;
                return ;
            }
            _numbers.push(performOp(first, second, token));
        }
    }
    if (_numbers.size() != 1)
    {
        std::cerr << "Error: invalid expression" << std::endl;
        return ;
    }
    std::cout << _numbers.top() << std::endl;
}
