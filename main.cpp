#include "Calculator.h"
#include <iostream>
int main(void) {
    Calculator calc;
    std::string str;
    std::getline(std::cin, str);
    while (!str.empty()) {
        calc.ReadString(str);
        std::cout << "Result:" << calc.Solve() << std::endl;
        std::getline(std::cin, str);
    }
    return 0;
}