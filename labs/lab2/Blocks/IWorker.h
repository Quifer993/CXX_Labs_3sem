#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include "constants.hpp"
#include <codecvt>

class IWorker{
public:
    virtual void work(std::vector<std::string> params, std::string& text) = 0;
    virtual size_t getNumberOfParams() = 0;
    virtual ~IWorker() = default;
};
