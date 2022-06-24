#pragma once
#ifndef _Parcer_
#define _Parcer_

#include <iostream>
#include <string>
#include <list>
#include <map>


typedef std::list< std::pair<std::wstring, int> > list_t;

class Parcer {
private:
	list_t listPair;
	std::map<std::wstring, int> inputFileMap;
public:
	Parcer() = default;
	~Parcer() = default;

	list_t getList();

	Parcer(std::map<std::wstring, int> mapDictionary) {	inputFileMap = mapDictionary; }
	
	void parcer();
};

#endif
