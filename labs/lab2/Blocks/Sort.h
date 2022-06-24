#pragma once
#include "BlockMaker.h"
#include "exceptionBlocks.hpp"

class Sort : public IWorker{
public:
    void work(std::vector<std::string> params, std::string& text);
    size_t getNumberOfParams() { return 0; };
};
