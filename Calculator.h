#pragma once
#include <string>
#include "Operation.h"
#include "Loader.h"
class Calculator {
private:
    std::map<std:: string, size_t> map;
    std::string input;
    Operation oper;
    Loader load;
public:
    Calculator();
    void ReadString(std::string str);
    void addDll();
    double Solve();
};
