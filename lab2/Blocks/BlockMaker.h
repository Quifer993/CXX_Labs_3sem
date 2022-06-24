#pragma once
//#include "BlockFactory.h"
#include "IBlockMaker.h"

template <class T>
class BlockMaker : public IBlockMaker{
public:
    BlockMaker<T>() = default;
    ~BlockMaker() = default;
    virtual IWorker* create() const{
        return new T();
    }

};
