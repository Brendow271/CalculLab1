#pragma once
#include <string>
#include "Operation.h"
class Calculator {
private:
    std::map<char, size_t> map;
    std::string input;
    Operation oper;
public:
    Calculator();
    void ReadString(std::string str);
    double Solve();
};