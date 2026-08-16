#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <climits>

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy)
    :_database(copy._database)
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
        _database = other._database;
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::loadDataBase(const std::string &filename)
{
    std::ifstream db(filename.c_str());
    if (!db.is_open())
    {
        std::cout << "Error: couldn't open database file" << std::endl;
        return;
    }
    std::string line;
    std::getline(db, line);
    while (std::getline(db, line))
    {
        size_t sep = line.find(',');
        char *end;
        std::string date = line.substr(0, sep);
        double exchange_rate = std::strtod(line.substr(sep + 1).c_str(), &end);
        _database.insert(std::make_pair(date, exchange_rate));
    }
    // std::map<std::string, double>::const_iterator cit;
    // for(cit = _database.begin(); cit != _database.end(); cit++)
    //     std::cout << "Key: " << cit->first << " Value: " << cit->second << std::endl;
    db.close();
}

std::string BitcoinExchange::trim(const std::string &str) const
{
    std::string::size_type start = 0;
    std::string::size_type end = str.size();

    while (start < end && std::isspace(str[start]))
        ++start;

    while (end > start && std::isspace(str[end - 1]))
        --end;

    return str.substr(start, end - start);
}

bool BitcoinExchange::isLeapYear(int year) const
{
    if (year % 400 == 0)
        return true;
    if (year % 100 == 0)
        return false;
    return (year % 4 == 0);
}

int BitcoinExchange::daysInMonth(int year, int month) const
{
    if (month == 2)
    {
        if (isLeapYear(year))
            return 29;
        return 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    return 31;
}

void BitcoinExchange::processInputFile(const std::string &filename)
{
    std::ifstream input(filename.c_str());
    if (!input.is_open())
    {
        std::cout << "Error: couldn't open input file" << std::endl;
        return;
    }

    std::string line;
    std::getline(input, line);
    while (std::getline(input, line))
    {
        size_t sep = line.find('|');
        if (sep == std::string::npos)
        {
            std::cout << "Error bad input => " << line << std::endl;
            continue;
        }
        std::string date = trim(line.substr(0, sep));
        std::string valueStr = trim(line.substr(sep + 1));
        char *end;
        if (!validateDateFormat(date))
        {
            std::cout << "Error: Not a valid date" << std::endl;
            continue;
        }
        double value = std::strtod(valueStr.c_str(), &end);
        if (*end != '\0')
        {
            std::cout << "Error: value not a number" << std::endl;
            continue;
        }
        if (!validateValue(value))
        {
            continue;
        }

        c_it exchangeRateIt = findExchangeRateEntry(date);
        if (exchangeRateIt == _database.end())
        {
            std::cout << "Error: No suitable exchange rate exists." << std::endl;
            continue;
        }
        std::cout << date << " => " << value << " = " << exchangeRateIt->second * value << std::endl;
    }
    input.close();
}

bool BitcoinExchange::validateDateFormat(const std::string &date) const
{
    if (date.size() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > daysInMonth(year, month))
        return false;

    return true;
}

bool BitcoinExchange::validateValue(double value) const
{
    if (value < 0)
    {
        std::cout << "Error: not a positive number." << std::endl;
        return false;
    }
    if (value > 1000)
    {
        std::cout << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
}

BitcoinExchange::c_it BitcoinExchange::findExchangeRateEntry(const std::string &date) const
{
    c_it exchangeRateIt = _database.lower_bound(date);
   
    if (exchangeRateIt != _database.end() && exchangeRateIt->first == date)
        return exchangeRateIt;
   
    if (exchangeRateIt == _database.begin())
        return _database.end();

    --exchangeRateIt;
    return exchangeRateIt;
}