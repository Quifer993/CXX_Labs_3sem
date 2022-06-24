#pragma once
#ifndef _Writing_
#define _Writing_

#include "parcer.hpp"
#include "readerConstants.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <codecvt>

class Write {
private:
	list_t listPair;
	int capacityWords;
	int capacityDifferentWords;
public:
	Write() = default;
	~Write() = default;

	Write(list_t list, int capacityW, int capacityDW);

	CodeError writeCSV(std::string nameFile);
};

#endif
