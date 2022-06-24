#pragma once
#include "BlockMaker.h"

class WriteFile : public IWorker{
public:
    void work(std::vector<std::string> params, std::string &text);
    size_t getNumberOfParams() { return 1; };
};
