#include "Parserr.hpp"

bool isNumber(std::string s){
    for (int i = 0; i < s.length(); i++){
        if ((s[i] < BEGIN_NUMBERS) || (s[i] > END_NUMBERS))  {return false; }
    }
    return true;
}

void error_desrip(){ throw std::runtime_error("Wrong scheme description!"); }

std::vector<size_t> Parser::getSchemeDescription()
{
    return schemeDescription;
}

mapParcer Parser::parse(BlockFactory& bf, std::string schemeFileName)
{
    std::ifstream schemeFile;
    std::string current;
    std::string currblockName;
    mapParcer blocks;

    schemeFile.open(schemeFileName);
    if (!schemeFile.is_open()){ throw std::runtime_error("Can't open scheme file!");}

    schemeFile >> current;
    if (current != START_PROGRAMM){ throw std::runtime_error("Wrong scheme description!");}

    while (true){
        std::vector<std::string> currParams;

        if( !(schemeFile >> current) ){ error_desrip(); }

        if (current == FINISH_PROGRAMM){ break;}
        if (!isNumber(current)){ error_desrip(); };
        size_t currBlockID = stoi(current);
        if( !(schemeFile >> current) || current != IS){ error_desrip(); }

        if( !(schemeFile >> current) ){ error_desrip(); }

        currblockName = current;

        IWorker* block;
        block = bf.createBlock(currblockName);
        size_t currentParamsNum = block->getNumberOfParams();

        for (size_t i = 0; i < currentParamsNum; i++){
            if( !(schemeFile >> current) ){ error_desrip(); }
            currParams.push_back(current);
        }
        if(blocks.find(currBlockID) != blocks.end()){ 
            throw std::runtime_error("Repeating nums of blocks!");
        }
        blocks[currBlockID] = make_pair(currblockName, currParams);

        delete block;
    }

    schemeDescription.clear();
    while (schemeFile >> current){
        if(isNumber(current)){ schemeDescription.push_back(stoi(current)); }
        else if (current != NEXT){ error_desrip(); }            
    }

    schemeFile.close();
    return blocks;
}
