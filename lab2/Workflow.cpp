#include "Workflow.hpp"

void workflowExecute(std::string schemeFile)
{
    BlockFactory factory;
    BlockFactory &bf = factory;
    
    // auto SortBlock =  BlockMaker<Sort>();
    // auto ReadFileBlock =  BlockMaker<ReadFile>();
    // auto DumpBlock =  BlockMaker<Dump>();
    // auto GrepBlock =  BlockMaker<Grep>();
    // auto WriteFileBlock =  BlockMaker<WriteFile>();
    // auto ReplaceBlock =  BlockMaker<WriteFile>();

    factory.registerNewBlock<Sort>("sort");
    factory.registerNewBlock<ReadFile>("readfile");
    factory.registerNewBlock<Dump>("dump");
    factory.registerNewBlock<Grep>("grep");
    factory.registerNewBlock<WriteFile>("writefile");
    factory.registerNewBlock<Replace>("replace");

    Parser parser;

    mapParcer blocks = parser.parse(bf, schemeFile);

    std::vector<size_t> chain = parser.getSchemeDescription();

    bool isFoundWriteFile = false;

    IWorker* block;
    std::string workString = EMPTY_STRING;

    for (size_t i = 0; i < chain.size(); i++){
        if(isFoundWriteFile){
            throw std::runtime_error("Writefile must stay at the end of programm!");
        }
        auto pair = blocks[chain[i]];
        if(pair.first == "writefile"){ 
            isFoundWriteFile = true; 
        }
        block = bf.createBlock(pair.first);
        try{
            block->work(pair.second, workString);
        }
        catch(TextException& e){
            std::cout << e.what() << "(Step " << i + 1 << ")" << std::endl;
        }
        catch(std::exception& e){
            delete block;
            std::cout << e.what() << std::endl;
            throw;
        }
        delete block;
    }
}
