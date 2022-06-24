#ifndef LAB3_SMARTBOT_H
#define LAB3_SMARTBOT_H

#include "IGamer.hpp"


//STATUS_SHIP checkShip(size_t point) {
//	if (1) {
//
//	}
//
//
//	return DEATH;
//}


class SmartBot : public IGamer {
private:
    bool isFind;
    bool isLeft;
    bool isRight;
    bool isUp;
    bool isDown;
    size_t shipsCount;
    size_t cellBroken;
    bool isRandom;

public:
    SmartBot() {
        isRandom = true;
        isFind = false;

        isLeft = false;
        isRight = false;
        isUp = false;
        isDown = false;

        shipsCount = GameConst::CAPACITY_ALL_SHIPS;
        cellBroken = GameConst::RANDOM_MORE100;
    }

    void breakShip(size_t *field, size_t point){
        if(!isFind){
            isLeft = false;
            isRight = false;
            isUp = false;
            isDown = false;
            if(checkWays(LEFT, point)){ isLeft = true;}
            if(checkWays(RIGHT, point)){ isRight = true;}
            if(checkWays(UP, point)){ isUp = true;}
            if(checkWays(DOWN, point)){ isDown = true;}
            isFind = true;
        }

        field[point] = BROKEN;
    }

    bool lessShipsCount(){
        isFind = false;
        shipsCount--;
        if(shipsCount == 0){
            return true;
        }
        return false;
    }

    bool isStep(size_t reaction, size_t *point, size_t numCell, const size_t* field){
        //        if(isFind){
        //
        //        }
        //        else {
        //            *point = rand() % AREA_FIELD;
        //        }
        //        *point = rand() % AREA_FIELD;
        if(isRandom){
            *point = rand() % GameConst::AREA_FIELD;
        }
        else{
            for(size_t i = 0; i < GameConst::AREA_FIELD; i++){
                if(field[i] >=SHIP1 && field[i] <= SHIP4){*point = i;}
            }//CHEATER
        }
        isRandom = !isRandom;

        return true;
    }

    size_t getTypePlayer() { return RND; };

};



#endif //LAB3_SMARTBOT_H
