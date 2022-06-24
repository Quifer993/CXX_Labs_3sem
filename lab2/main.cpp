#include "Workflow.hpp"

int main(int argc, char **argv){
    std::vector<std::string> files(16);
    files[0]  = "input.txt";
        files[2] = "input_with_bad_reading.txt";
    files[3] = "input_with_bad_writefile.txt";
    files[4] = "input_with_reading_in_the_middle.txt";
    files[5] = "input_with_negative_nums_of_blocks.txt";
    files[6] = "input_with_repeating_nums_of_blocks.txt";
    files[7] = "input_with_wrong_separator1.txt";
    files[8] = "input_with_wrong_separator2.txt";
    files[9] = "input_without_csed.txt";
    files[10] = "input_without_desc.txt";
    files[11] = "input_without_readfile.txt";
    files[12] = "input2.txt";
    files[13] = "input3.txt";
    files[14] = "input4.txt";
    files[15] = "sing.txt";
    size_t i = 0;
    for(i = 0; i < 15; i ++){
        std::cout << "(File number " << i + 1 << ")" << std::endl;
        try{
            std::string instructions = files[i];
            workflowExecute(instructions);
        }
        catch(std::exception e){
            std::cout << e.what() << std::endl ;
        }
    }

    // argc == ONLY_EXE ? instructions = INPUT_STANDART1 : instructions = argv[FROM_FILE];
    return 0;
}
