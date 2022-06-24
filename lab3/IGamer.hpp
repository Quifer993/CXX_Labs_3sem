#pragma once

#include "SFML/include/SFML/Graphics.hpp"
#include "constants.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

enum BUTTON_TYPE {
    NOTHING,
    START_GAME,
    EXIT_GAME,
    RND1,
    RND2,
    SMARTRND1,
    SMARTRND2,
    REAL1,
    REAL2,

    MENU,
    ONE_BLOCK,
    TWO_BLOCK,
    THREE_BLOCK,
    FOUR_BLOCK,

    CONTINUE_MICRO_MENU,
    STOP_MICRO_MENU,
    EXIT_MICRO_MENU

};

enum CAGE_STATUS {
    EMPTY,
	SHIP1,
	SHIP2,
	SHIP3,
	SHIP4,
	NEAR_SHIP,

	POINT,
	BROKEN,
	KILLED
};

enum TYPE_GAMER {
	RND,
	REAL
};

enum WAYS {
	RIGHT,
	LEFT,
	UP,
	DOWN

};


class IGamer {
public:
	virtual size_t getTypePlayer() { return RND; };

	virtual void breakShip(size_t *field,size_t point){
	    field[point] = BROKEN;
	}
	virtual ~IGamer() = default;
	virtual bool isHavePlacesForShips(size_t typeBlock){ return true; }
	virtual bool isReady(){ return true; }
	virtual void addShip(size_t typeSetBlock) {return;};
	virtual bool lessShipsCount() = 0;
	virtual bool isAllShipsType(const size_t type) {return true;}
	virtual bool isStep(size_t reaction, size_t *point, size_t numCell, const size_t* field){
	    *point = rand() % GameConst::AREA_FIELD;
	   return true;
	}

//	void fillingCage(size_t size, sf::RenderWindow* window);



};

bool checkWays(size_t type, size_t next);