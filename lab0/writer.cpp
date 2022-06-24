#include "writer.hpp"
#include <iomanip>


Write::Write( list_t list, int capacityW, int capacityDW) {
	listPair = list;
	capacityWords = capacityW;
	capacityDifferentWords = capacityDW;
}


CodeError Write::writeCSV(std::string nameOutputFile) {
	std::wofstream outputFile(nameOutputFile);
	if (!outputFile.is_open()) {
		return CodeError::FILE_NOT_OPEN;
	}
	const std::locale utf8 = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
	outputFile.imbue(utf8);

	std::setiosflags(std::ios::left);
	for (auto& item : listPair){
		outputFile << item.first << ";";
		outputFile << item.second << ";";
		outputFile << ((double)item.second / (double)capacityWords) * 100 << "%" << std::endl;
		
		/*setlocale(LC_ALL, "Russian");
		std::wcout << item.first << std::setw(25 - item.first.length());
		std::wcout << item.second << std::setw(10);
		std::wcout << ((double)item.second / (double)capacityWords) * 100 << "%" << std::endl;
		---Just for tests in stdout---
		*/

	}

	outputFile.close();
	return CodeError::OK;
}
