#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
private:
    std::map<std::string, double> _data;

    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);

public:
    BitcoinExchange();
    ~BitcoinExchange();

    void loadDatabase(const std::string& filename);
    void processInputFile(const std::string& filename);

private:
    bool isValidDate(const std::string& date) const;
    bool isValidValue(const std::string& valueStr, double& value) const;
    double getExchangeRate(const std::string& date) const;
    std::string trim(const std::string& str) const;
};

#endif
