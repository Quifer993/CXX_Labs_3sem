#include "ReadFile.h"

void ReadFile::work(std::vector<std::string> params, std::string& text){
    if (params.empty()){
        throw std::runtime_error("Too few arguments for reading input file");
    }

    //params[0] = FileName
    std::ifstream input_file;
    input_file.open(params[FILE_NAME]);

	const std::locale utf8 = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
	input_file.imbue(utf8);

    if (!input_file.is_open()){
        throw std::runtime_error("Can't open input file");
    }

    text = "";
    std::string data;
    while (getline(input_file, data)){
        text += data + LINE_BREAK;
    }
    
    input_file.close();
};
