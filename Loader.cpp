#include "Loader.h"

void Loader::loadDll() {
    WIN32_FIND_DATAA wfd;

    HANDLE const hFind = FindFirstFileA((pluginsPath + std::string("*.dll")).c_str(), &wfd);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            std::string dllFileName(wfd.cFileName);
            getFunc(dllFileName);
        } while (NULL != FindNextFileA(hFind, &wfd));

        FindClose(hFind);
    }
    else
    {
       throw std::runtime_error("invalid plugin path");
    }
}

void Loader::getFunc(std::string const& fileName) {
    std::string tmp = (pluginsPath + fileName);
    HMODULE hm = LoadLibraryA((pluginsPath + fileName).c_str());
    auto error = GetLastError();
    if (hm == nullptr) {
        throw std::runtime_error("dll not found");
    }

    std::string funcName = fileName;
    funcName.erase(0,3).erase(funcName.find('.'),4);

    binaryFunction bfunc = (binaryFunction)GetProcAddress(hm, "binOper");
    if (bfunc == nullptr)
    {
        unaryFunction ufunc = (unaryFunction)GetProcAddress(hm, "uniOper");
        if (ufunc == nullptr)
        {
            throw std::runtime_error("function not found");
        }
        unaryFunctions.insert(std::pair<std::string, unaryFunction>(funcName, ufunc));
    }
    else
    {
        binaryFunctions.insert(std::pair<std::string, binaryFunction>(funcName, bfunc));
    }
}

double Loader::makeOperation(double const& a, std::string const& funcName, double const& b) {
    if (unaryFunctions.contains(funcName)) {
        return unaryFunctions[funcName](a);
    }
    else if (binaryFunctions.contains(funcName)) {
        return binaryFunctions[funcName](a, b);
    }
}

bool Loader::containsUnaryFunc(std::string const& funcName) const {
    return unaryFunctions.contains(funcName);
}

bool Loader::containsBinaryFunc(std::string const& funcName) const {
    return binaryFunctions.contains(funcName);
}