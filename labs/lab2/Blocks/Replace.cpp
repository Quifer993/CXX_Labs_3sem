#include "Replace.h"

void Replace::work(std::vector<std::string> params, std::string& text){
    if (text.empty()){
        throw TextException("Work text is empty", "Replace");
    }

    //params[0] == word1
    //params[1] == word2
    if (params.size() != 2){
        throw std::runtime_error("Too few parameters to replace!");
    }
    if (params[OLD_WORD_NUM].size() != params[NEW_WORD_NUM].size()){
        throw TextException("Words have different sizes", "Replace");
    }

    std::string oldWord = params[OLD_WORD_NUM];
    std::string newWord = params[NEW_WORD_NUM];

    size_t pos = text.find(oldWord);
    while (pos != std::string::npos){
        text.replace(pos, oldWord.size(), newWord);
        pos = text.find(oldWord, pos);
    }
}
