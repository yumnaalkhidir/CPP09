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
//the above canonical for funtions are simple and basicaly empty cause i dont have anythign to assign 

//this function trims whit spaces from the beginging and end of a string
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

//checks for a leap year if the year is divisibly by 4 and not by 100 then
//its a leap year also if its a century year if its divisibly by 400 its a leap year
bool BitcoinExchange::isLeapYear(int year) const
{
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

//return the days in a month
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
//this functions checks if the date is in the correct format year-month-day or 0000-00-00
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
// this function checks if my value is positive and not greater that 1000
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
//loads the database into a map container key = date value= exchange rate it uses getline to fetch each line
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
//finds the rate of a specific date and returns an iterator using the lowerbound function but 
//if the echangerate is not pointing the the end and it is pointing to the same date then return the result
//if the iteratir fiund is pointing to the begining it means no match have been found or its the earlier than the first date in the database
//else decreese the iterator and returnit
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
//this is the core funtion that joins everything together
//first it check if the file passed opens safely
//then goes through line by line speerates the lines by | and trims the substring
//checks for valid dat and value then extracts the date and print the mulitplied result 
//appropriet eeror messages are being written 
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
