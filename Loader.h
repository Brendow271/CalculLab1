#pragma once
#include<iostream>
#include<map>
#include<Windows.h>


using unaryFunction = double(*)(double);
using binaryFunction = double(*)(double, double);
using mapBinaryFunction = std::map<std::string, double(*)(double, double)>;
using mapUnaryFunction = std::map<std::string, double(*)(double)>;

class Loader {
public:
    Loader() { loadDll(); }
    double makeOperation(double const& a, std::string const& funcName, double const& b = 0.0);
    bool containsUnaryFunc(std::string const& funcName) const;
    bool containsBinaryFunc(std::string const& funcName) const;
private:
    std::string pluginsPath = "./plugins/";
    mapUnaryFunction unaryFunctions;
    mapBinaryFunction binaryFunctions;
    void loadDll();
    void getFunc(std::string const& fileName);
};