#include "reader.hpp"


Read::Read() = default;
Read::~Read() = default;


Read::Read(std::string nameFile) {
	readMap;
	capacityWords = 0;
	capacityDifferentWords = 0;
};


int Read::getCapacityWords() {	return this->capacityWords; }
int Read::getCapacityDifferentWords() {	return this->capacityDifferentWords; }
std::map<std::wstring, int> Read::getMap() { return this->readMap; }

void Read::addWordAtMap(bool isCorrectWord,
							std::wstring inputString, 
							int endPoint, 
							int beginNewWord) 
{
	if (!isCorrectWord) { return; }
	capacityWords++;
	std::wstring newWord = inputString.substr(beginNewWord, endPoint - beginNewWord);
	auto it = readMap.find(newWord);
	if (readMap.count(newWord)) {
		(it->second)++;
	}
	else {
		readMap.emplace(newWord, 1);
		capacityDifferentWords++;
	}
};


CodeError Read::readingFile(std::string nameFile) {
	std::wifstream file;

	const std::locale utf8 = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
	file.imbue(utf8);
	file.open(nameFile);
	if (!file.is_open()) {
		return CodeError::FILE_NOT_OPEN;
	}


	std::wstring inputString;
	std::locale loc(UTF8);
	while (!file.eof()) {
		std::getline(file, inputString);

		int beginNewWord = 0;
		int length = inputString.length();
		bool isCorrectWord = false;

		for (int i = 0; i < length; i++) {
			int isNum = (inputString[i] >= '0' && inputString[i] <= '9');
			if ( isNum || std::isalpha(inputString[i], loc) ){
				isCorrectWord = true;
				continue;
			}
			else {
				addWordAtMap(isCorrectWord ,inputString, i, beginNewWord);
				isCorrectWord = 0;
				beginNewWord = i + 1;
			}
		}
		addWordAtMap(isCorrectWord, inputString, length, beginNewWord);
	}

	file.close();
	return CodeError::OK;
}
