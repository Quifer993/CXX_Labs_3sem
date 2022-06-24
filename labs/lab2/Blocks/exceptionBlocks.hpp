#pragma once
#include <exception>

class TextException : std::exception{
    private:
        std::string type;
        std::string where;
    public:
        TextException(std::string type_error, std::string where_is_error): type(type_error), where(where_is_error){};
        std::string what(){
            return "Error: '" + type + "' happened in the block '" + where + "'";
        }
};
