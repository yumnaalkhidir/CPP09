#ifndef BIITCOINEXCHANGE_HPP
#define BIITCOINEXCHANGE_HPP
#include <map>
#include <string>

class BitcoinExchange
{
    private:

        std::map<std::string, double> _database;
        typedef std::map<std::string, double>::const_iterator c_it;
        
        bool validateDateFormat(const std::string &date) const;
        bool validateValue(double value) const;
        c_it findExchangeRateEntry(const std::string &date) const;
        std::string trim(const std::string &str) const;
        bool isLeapYear(int year) const;

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& copy);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        void loadDataBase(const std::string &filename);
        void processInputFile(const std::string &filename);

        int daysInMonth(int year, int month) const;
};
#endif