#pragma once
#include "IWorker.h"

class IBlockMaker{
public:
    virtual IWorker* create() const = 0;
    virtual ~IBlockMaker() = default;
};
