#include "Sort.h"

void Sort::work(std::vector<std::string> params, std::string& text){
    if (text.empty()){
        throw TextException("Work text is empty", "Sort");
    }

    std::vector<std::string> strings;
    std::string currentStr = EMPTY_STRING;
    char currentSymb;
    
    for (size_t i = 0; i < text.size(); i++){
        currentSymb = text.at(i);
        if ((currentSymb != LINE_BREAK) && (i != text.size() - 1)){
            currentStr += currentSymb;
        }
        else{
            strings.push_back(currentStr + LINE_BREAK);
            currentStr = EMPTY_STRING;
        }
    }

    std::sort(strings.begin(), strings.end());
    std::string ret_string = EMPTY_STRING;
    for (size_t i = 0; i < strings.size(); i++){
        ret_string += strings[i];
    }
    text = ret_string;
}
