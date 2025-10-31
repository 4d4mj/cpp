#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _data(other._data) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        _data = other._data;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

std::string BitcoinExchange::trim(const std::string& str) const {
    size_t start = 0;
    size_t end = str.length();

    while (start < end && std::isspace(str[start])) {
        start++;
    }
    while (end > start && std::isspace(str[end - 1])) {
        end--;
    }
    return str.substr(start, end - start);
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }

    for (size_t i = 0; i < date.length(); i++) {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(date[i])) {
            return false;
        }
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 1900 || year > 3000) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeap ? 29 : 28)) return false;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) return false;
    }

    return true;
}

bool BitcoinExchange::isValidValue(const std::string& valueStr, double& value) const {
    char* endptr;
    value = std::strtod(valueStr.c_str(), &endptr);

    if (*endptr != '\0' && !std::isspace(*endptr)) {
        return false;
    }

    return true;
}

double BitcoinExchange::getExchangeRate(const std::string& date) const {
    std::map<std::string, double>::const_iterator it = _data.find(date);
    if (it != _data.end()) {
        return it->second;
    }

    it = _data.lower_bound(date);
    if (it == _data.begin()) {
        return it->second;
    }

    --it;
    return it->second;
}

void BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Error: could not open database file.");
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos) {
            continue;
        }

        std::string date = trim(line.substr(0, commaPos));
        std::string valueStr = trim(line.substr(commaPos + 1));

        double value;
        if (isValidDate(date) && isValidValue(valueStr, value)) {
            _data[date] = value;
        }
    }

    file.close();
}

void BitcoinExchange::processInputFile(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        size_t pipePos = line.find('|');
        if (pipePos == std::string::npos) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date = trim(line.substr(0, pipePos));
        std::string valueStr = trim(line.substr(pipePos + 1));

        if (!isValidDate(date)) {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        double value;
        if (!isValidValue(valueStr, value)) {
            std::cerr << "Error: bad input => " << valueStr << std::endl;
            continue;
        }

        if (value < 0) {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }

        if (value > 1000) {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        double rate = getExchangeRate(date);
        std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
    }

    file.close();
}
