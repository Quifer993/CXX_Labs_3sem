#ifndef LAB3_REALPLAYER_H
#define LAB3_REALPLAYER_H

#include "IGamer.hpp"


class RealPlayer : public IGamer {
private:
    size_t counterShips[5];
    size_t shipsSetCount;
    size_t shipsCount;

public:
    RealPlayer() {
        counterShips[4] = GameConst::COUNT_SHIPS4;
        counterShips[3] = GameConst::COUNT_SHIPS3;
        counterShips[2] = GameConst::COUNT_SHIPS2;
        counterShips[1] = GameConst::COUNT_SHIPS1;
        shipsSetCount = GameConst::CAPACITY_ALL_SHIPS;
        shipsCount =  GameConst::CAPACITY_ALL_SHIPS;

    }

    ~RealPlayer() = default;
    bool lessShipsCount(){
        shipsCount--;
        if(shipsCount == 0){
            return true;
        }
        return false;
    }

    size_t getTypePlayer() { return REAL; };

    bool isAllShipsType(const size_t type){
        return counterShips[type] == 0;
    }

    bool isStep(size_t reaction, size_t *point, size_t numCell, const size_t* field){
        if(numCell != GameConst::RANDOM_MORE100){
            *point = numCell;
            return true;
        }
        return false;
    }

    bool isReady(){ return shipsSetCount == 0; }

    void addShip(size_t typeSetBlock){
        shipsSetCount--;
        counterShips[typeSetBlock - ONE_BLOCK + 1]--;
    }

    bool isHavePlacesForShips(size_t typeBlock){
        return counterShips[typeBlock - ONE_BLOCK + 1] > 0;
    }

};






#endif //LAB3_REALPLAYER_H
