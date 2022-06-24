#pragma once
#include "IGamer.hpp"


class StupidBot : public IGamer {
private:
    size_t shipsCount;
public:
    StupidBot() { shipsCount = GameConst::CAPACITY_ALL_SHIPS; }

    bool lessShipsCount(){
        shipsCount--;
        if(shipsCount == 0){
            return true;
        }
        return false;
    }

	size_t getTypePlayer() { return RND; };

};

