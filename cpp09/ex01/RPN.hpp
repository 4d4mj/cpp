#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>

class RPN {
private:
    std::stack<int> _stack;

    RPN(const RPN& other);
    RPN& operator=(const RPN& other);

public:
    RPN();
    ~RPN();

    int evaluate(const std::string& expression);

private:
    bool isOperator(const std::string& token) const;
    int performOperation(int a, int b, char op) const;
};

#endif
