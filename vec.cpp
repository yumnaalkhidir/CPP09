#include <vector>

#include <iostream>
#include <utility>
int main(void)
{
    std::vector<std::pair<int, int>> pairs;
    pairs.push_back(std::make_pair(3,4));

    auto it = pairs.begin();
    for (; it != pairs.end(); it++)
    {
        std::cout << it->first << std::endl;
        std::cout << it->second << std::endl;
    }
}