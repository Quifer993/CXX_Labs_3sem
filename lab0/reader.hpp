#pragma once
#ifndef _Reading_
#define _Reading_

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <cctype>
#include <codecvt>
#include "readerConstants.hpp"


class Read {
private:
	std::map<std::wstring, int> readMap;
	int capacityWords;
	int capacityDifferentWords;

	void addWordAtMap(bool isCorrectWord, std::wstring inputString, int endPoint, int beginNewWord);
public:


	Read();
	~Read();

	int getCapacityDifferentWords();
	int getCapacityWords();
	std::map<std::wstring, int> getMap();
	

	Read(std::string nameFile);

	CodeError readingFile(std::string nameFile);
};

#endif
