#pragma once

#include<iostream>
#include<map>
#include<functional>
#include <iostream>
#include <stack>
#include <cctype>
#include <map>
#include <algorithm>
#include <string>
using mapOperators = std::map<std::string, std::function<double(double, double)>>;
class Operation {
    Operation(const Operation&) = delete;
    Operation& operator=(Operation const&) = delete;
    mapOperators operations;
public:
    Operation();
    double operation(double const& a, std::string const& name, double const& b);
};