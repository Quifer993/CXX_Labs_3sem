#include "Grep.h"


bool containsWord(std::string text, std::string word){
    if (text.find(word) != std::string::npos)
    { return true; }
    else{ return false; }
}

void Grep::work(std::vector<std::string> params, std::string& text){
    if (params.empty()){
        throw std::runtime_error("Too few arguments to find in text!");
    }

    if (text.empty()){
        throw TextException("Work text is empty", "Grep");
    }

    if (params[0] == EMPTY_STRING){
        throw TextException("Word to find is empty", "Grep");
    }

    std::vector<std::string> strings;
    std::string currentStr = EMPTY_STRING;
    char currentSymb;
    size_t i = 0;

    size_t end = text.size();
    while (i < end){
        currentSymb = text.at(i);
        if ((currentSymb != LINE_BREAK) && (i != end - 1)){
            currentStr += currentSymb;
        }
        else{
            strings.push_back(currentStr + LINE_BREAK);
            currentStr = EMPTY_STRING;
        }
        i++;
    }
    std::string ret_text = EMPTY_STRING;
    for (i = 0; i < strings.size(); i++){
        if (containsWord(strings[i], params[0])){
            ret_text += strings[i];
        }
    }
    text = ret_text;
}
