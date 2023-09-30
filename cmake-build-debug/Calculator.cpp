#include "Calculator.h"
#include "Operation.h"
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <map>
#include <stack>
#include <cmath>
#include <filesystem>
#include <windows.h>
#include "Loader.h"

Calculator::Calculator() {
    map.insert(std::make_pair('(', 1));
    map.insert(std::make_pair('+', 2));
    map.insert(std::make_pair('-', 2));
    map.insert(std::make_pair('*', 3));
    map.insert(std::make_pair('/', 3));
    map.insert(std::make_pair('^', 4));
    map.insert(std::make_pair('s', 5));
    map.insert(std::make_pair('c', 5));
    map.insert(std::make_pair('l', 5));
}
void Calculator::ReadString(std::string str) {
    std::string res;
    std::string::size_type ind;
    while ((ind = str.find(' ')) != std::string::npos)
    {
        str.erase(ind, 1);
    }
    for (int i = 0; i < str.size(); ++i) {
        auto c = str[i];
        if (isalpha(c)) {
            if ((str[i + 1]) && (str[i + 2])) {
                if ((c == 's') && (str[i + 1] == 'i') && (str[i + 2] == 'n')) {
                    i += 2;
                    continue;
                }
                if ((c == 'c') && (str[i + 1] == 'o') && (str[i + 2] == 's')) {
                    i += 2;
                    continue;
                }
                if ((c == 'l') && (str[i + 1] == 'n')) {
                    i++;
                    continue;
                }
                throw std::exception("uncorrect expression");
            }
            throw std::exception("uncorrect expression");
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
                throw std::exception("uncorrect expression");
            }
        }
    }
    if (count != 0) {
        throw std::exception("uncorrect expression");
    }
    for (int i = 0; i < str.size(); ++i)
    {
        if ((str[i] == '+' || str[i] == '-') && (0 == i || (!isalnum(str[i - 1]) && str[i - 1] != '.' && str[i - 1] != ')')))
        {
            auto it = std::find_if(str.begin() + i + 1, str.end(), [](char const c) {return !isalnum(c); });
            str.insert(it, ')');
            str.insert(i, "(0");
            int nnn = 0;
        }
    }
    while ((ind = str.find("sin")) != std::string::npos)
    {
        str.erase(ind + 1, 2);
    }
    while ((ind = str.find("cos")) != std::string::npos)
    {
        str.erase(ind + 1, 2);
    }
    while ((ind = str.find("ln")) != std::string::npos)
    {
        str.erase(ind + 1, 1);
    }
    std::stack<char> stack;
    for (auto c : str)
    {
        if (!isdigit(c) && ('.' != c))
        {
            res += ' ';
            if (')' == c)
            {
                while (stack.top() != '(')
                {
                    res += stack.top();
                    stack.pop();
                    res += ' ';
                }
                stack.pop();
            }
            else if ('(' == c)
            {
                stack.push(c);
            }
            else if (stack.empty() || (map[stack.top()] < map[c]))
            {
                stack.push(c);
            }
            else
            {
                do
                {
                    res += stack.top();
                    res += ' ';
                    stack.pop();
                } while (!(stack.empty() || (map[stack.top()] < map[c])));
                stack.push(c);
            }
        }
        else
        {
            res += c;
        }
    }
    while (!stack.empty())
    {
        res += ' ';
        res += stack.top();
        stack.pop();
    }
    input = res;
}


double Calculator::Solve() {
    Loader load;
    double a, b;
    std::stack<double> stack;
    std::string s;
    std::stringstream  tmp(input);
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