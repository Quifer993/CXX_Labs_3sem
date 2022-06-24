#pragma once
#include "BlockMaker.h"

class BlockFactory{
private:
    std::map<std::string, IBlockMaker*> blockMap;
public:
    IWorker* createBlock(std::string blockName){
        auto block = blockMap.find(blockName);
        IBlockMaker* blockMaker = block->second;
        return blockMaker->create();
    }

    template<class T>   void registerNewBlock(std::string newBlockName){
        //if (blockMap.find(newBlockName) != blockMap.end() ) throw std::runtime_error("Multiple registering of block");
        if (blockMap.find(newBlockName) != blockMap.end()){
            throw std::runtime_error("Multiple registering of block");
        }
        BlockMaker<T> *block = new BlockMaker<T>();
        blockMap[newBlockName] = block;
    }
    
    BlockFactory() = default;
    ~BlockFactory(){
        for(auto it = blockMap.begin(); it != blockMap.end(); ++it) {
            delete it->second;
        }

    }
};
