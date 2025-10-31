#include "RPN.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

RPN::RPN() {}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN& RPN::operator=(const RPN& other) {
    if (this != &other) {
        _stack = other._stack;
    }
    return *this;
}

RPN::~RPN() {}

bool RPN::isOperator(const std::string& token) const {
    return token.length() == 1 &&
           (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/');
}

int RPN::performOperation(int a, int b, char op) const {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0) {
                throw std::runtime_error("Error: division by zero");
            }
            return a / b;
        default:
            throw std::runtime_error("Error: invalid operator");
    }
}

int RPN::evaluate(const std::string& expression) {
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        if (isOperator(token)) {
            if (_stack.size() < 2) {
                throw std::runtime_error("Error");
            }

            int b = _stack.top();
            _stack.pop();
            int a = _stack.top();
            _stack.pop();

            int result = performOperation(a, b, token[0]);
            _stack.push(result);
        }
        else {
            if (token.length() != 1 || !std::isdigit(token[0])) {
                throw std::runtime_error("Error");
            }

            int num = token[0] - '0';
            _stack.push(num);
        }
    }

    if (_stack.size() != 1) {
        throw std::runtime_error("Error");
    }

    return _stack.top();
}
