#pragma once
#include "Blocks/Sort.h"
#include "Blocks/Replace.h"
#include "Blocks/Dump.h"
#include "Blocks/Grep.h"
#include "Blocks/WriteFile.h"
#include "Blocks/ReadFile.h"
#include "Blocks/BlockFactory.h"

typedef std::map<size_t, std::pair<std::string, std::vector<std::string>>> mapParcer;

class Parser
{
private:
    std::vector<size_t> schemeDescription;
public:
    mapParcer parse(BlockFactory& bf, std::string schemeFile);
    std::vector<size_t> getSchemeDescription();
};
