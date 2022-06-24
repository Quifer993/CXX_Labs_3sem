#include "WriteFile.h"


void WriteFile::work(std::vector<std::string> params, std::string& text){
    if (params.empty()){
        throw std::runtime_error("Too few arguments for writing into output file");
    }

    std::ofstream output_file;
    output_file.open(params[FILE_NAME]);

	const std::locale utf8 = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
	output_file.imbue(utf8);

    if (!output_file.is_open()){
        throw std::runtime_error("Can't open output file");
    }

    output_file << text;
    output_file.close();
};
