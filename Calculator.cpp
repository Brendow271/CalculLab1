#include "Calculator.h"
#include <iostream>
#include <sstream>
#include <map>
#include <stack>


Calculator::Calculator() {
    map.insert(std::make_pair("(", 1));
    map.insert(std::make_pair("+", 2));
    map.insert(std::make_pair("-", 2));
    map.insert(std::make_pair("*", 3));
    map.insert(std::make_pair("/", 3));
//    map.insert(std::make_pair('^', 4));
//    map.insert(std::make_pair('s', 5));
//    map.insert(std::make_pair('c', 5));
//    map.insert(std::make_pair('l', 5));
}
void Calculator::ReadString(std::string str) {
    std::string res;
    std::string::size_type ind;
    std::string tempStr = "";
    while ((ind = str.find(' ')) != std::string::npos)
    {
        str.erase(ind, 1);
    }
    for (int i = 0; i < str.size(); i++) {
        char c = str[i];
        while(isalpha(c))
        {
            tempStr += c;
            if (++i < str.length())
                c = str[i];

        }
        if(!(c >= '0' && c <= '9') && !(map.contains({c})))
        {
            if (!(load.containsUnaryFunc(tempStr) || load.containsBinaryFunc(tempStr)))
                throw std::runtime_error("incorrect expression1");
            else
            {
                map.insert(std::make_pair(tempStr,4));
            }
            tempStr = "";
        }
    }
    int count = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '(') {
            count++;
            continue;
        }
        if (str[i] == ')') {
            count--;
            if (count < 0) {
                throw std::runtime_error("incorrect expression2");
            }
        }
    }
    if (count != 0) {
        throw std::runtime_error("incorrect expression3");
    }
    for (int i = 0; i < str.size(); ++i)
    {
        if ((str[i] == '+' || str[i] == '-') && (0 == i || (!isalnum(str[i - 1]) && str[i - 1] != '.' && str[i - 1] != ')')))
        {
            auto it = std::find_if(str.begin() + i + 1, str.end(), [](char const c) {return !isalnum(c); });
            str.insert(it, ')');
            str.insert(i, "(0");
        }
    }

    std::stack<std:: string> stack;
    for (int i = 0; i < str.length(); i++)
    {
        std:: string c = {str[i]};
        if (!(c >= "0" && c <= "9") && ("." != c))
        {
            res += " ";
            if (")" == c)
            {
                while (stack.top() != "(")
                {
                    res += stack.top();
                    stack.pop();
                    res += ' ';
                }
                stack.pop();
            }
            else if ("(" == c)
            {
                stack.push(c);
            }
            else if ((stack.empty() || map[stack.top()] < map[c]) && (load.containsUnaryFunc(c) || load.containsBinaryFunc(c)))
            {
                stack.push(c);
            }
            else
            {
                while(!(load.containsUnaryFunc(tempStr) || load.containsBinaryFunc(tempStr)))
                {
                    tempStr += c;
                    if (++i< str.length())
                        c = str[i];
                    else break;
                }
                --i;
                stack.push(tempStr);

                do
                {
                    res += stack.top();
                    res += " ";
                    stack.pop();
                }while (!(stack.empty() || (map[stack.top()] < map[c])));
            }
        }
        else
        {
            res += c;
        }
    }
    while (!stack.empty())
    {
        res += " ";
        res += stack.top();
        stack.pop();
    }
    input = res;
}


double Calculator::Solve() {
    double a, b;
    std::stack<double> stack;
    std::string s;
    std::stringstream tmp(input);
    for (; tmp >> s;) {
        if (!isdigit(s[0])) {
            a = 0.0;
            b = 0.0;
            a = stack.top();
            stack.pop();
            if (load.containsUnaryFunc(s)) {
                stack.push(load.makeOperation(a, s, b));
                continue;
            }
            b = stack.top();
            stack.pop();
            if (load.containsBinaryFunc(s)) {
                stack.push(load.makeOperation(a, s, b));
                continue;
            }
            stack.push(oper.operation(a, s, b));
        }
        else {
            stack.push(std::stod(s));
        }
    }
    return stack.top();
}

void Calculator :: addDll(){
    Loader();
};