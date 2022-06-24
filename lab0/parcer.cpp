#include "parcer.hpp"


list_t Parcer::getList() { return this->listPair; }


void Parcer::parcer() {
    for (auto& item : inputFileMap){
        listPair.push_back(item);
    }

    listPair.sort([](const std::pair<std::wstring, int>& element1, const std::pair<std::wstring, int>& element2)
        {
            if (element1.second == element2.second)
                return element1 > element2;
            return element1.second > element2.second;
        }
    );

}
