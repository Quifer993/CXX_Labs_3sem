#pragma once
#include "IGamer.hpp"
bool checkWays(size_t type, size_t next){
    if(type == LEFT){ return next % GameConst::LENGTH_FIELD_IN_CELLS != 0;}
    else if(type == RIGHT){ return next % GameConst::LENGTH_FIELD_IN_CELLS != GameConst::LENGTH_FIELD_IN_CELLS - 1;}
    else if (type == UP){ return next / GameConst::LENGTH_FIELD_IN_CELLS != 0;}
    else { return next / GameConst::LENGTH_FIELD_IN_CELLS != GameConst::LENGTH_FIELD_IN_CELLS - 1;}//END

}