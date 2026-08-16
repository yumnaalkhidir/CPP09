#ifndef RPN_HPP
#define RPN_HPP
#include <stack>
#include <iostream>
#include<string>
#include <cctype>
class RPN
{
    private:
        std::stack<int> _numbers;

        bool isValidArg(std::string arg) const;
        int performOp(int first, int second, char op) const;
    public:
        RPN();
        RPN(const RPN& copy);
        RPN& operator=(const RPN& copy);
        ~RPN();

        void calculate(const std::string &expression);
};

#endif