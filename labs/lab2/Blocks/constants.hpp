#pragma once

const int FILE_NAME = 0;
const std::string EMPTY_STRING = "";
const std::string NEXT = "->";
const char LINE_BREAK = '\n';
const int OLD_WORD_NUM = 0;
const int NEW_WORD_NUM = 1;
const char BEGIN_NUMBERS = '0';
const char END_NUMBERS = '9';
const std::string IS = "=";
const std::string START_PROGRAMM = "desc";
const std::string FINISH_PROGRAMM = "csed";
// const std::string INPUT_STANDART1 = "input.txt";

const int ONLY_EXE = 1;
const int FROM_FILE = 1;



enum class BLOCK_TYPE{
    INPUT = 0,
    OUTPUT = 1,
    MODIFICATION = 2
};