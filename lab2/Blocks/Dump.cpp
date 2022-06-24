#include "Dump.h"

void Dump::work(std::vector<std::string> params, std::string& text){
    if (params.empty()){
        throw std::runtime_error("Too few arguments for writing into output file");
    }

    std::ofstream output_file;
    output_file.open(params[FILE_NAME]);

    if (!output_file.is_open()){
        throw std::runtime_error("Can't open output file");
    }

    if (text.empty()){
        throw TextException("Nothing to write", "Grep");
    }
    output_file << text;
    output_file.close();
}
