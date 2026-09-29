#ifndef RPN_HPP
#define RPN_HPP
#include <stack>
#include <list>
#include<string>

class RPN
{
    private:
        std::stack<int, std::list<int> > _numbers;

        int performOp(int first, int second, char op) const;
        
    public:
        RPN();
        RPN(const RPN& copy);
        RPN& operator=(const RPN& copy);
        ~RPN();
        
        bool isValidArg(std::string arg) const;
        void calculate(const std::string &expression);
};

#endif