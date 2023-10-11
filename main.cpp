#include "Calculator.h"
#include <iostream>
int main(void) {
    Calculator calc;
    calc.addDll();
    std::string str;
    std::getline(std::cin, str);
    while (!str.empty()) {
        try{
            calc.ReadString(str);
            std::cout << "Result:" << calc.Solve() << std::endl;
        }
        catch(const std:: exception& error){
            std::cerr << error.what() << std :: endl;
        }
        std::getline(std::cin, str);
    }
    return 0;
}