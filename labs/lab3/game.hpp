#pragma once
#include "Stupid.hpp"
#include "SmartBot.h"
#include "RealPlayer.h"


class Game {
private:
	size_t* Field1;
	size_t* Field2;

	size_t reaction;
	bool isSet;
	bool mustStopGame;
	size_t typeSetBlock;
	size_t winner;

	sf::Texture background;
	sf::Texture field1;
	sf::Texture field2;
	sf::Texture menuBut;

	sf::Texture texOneBlock;
	sf::Texture texTwoBlock;
	sf::Texture texThreeBlock;
	sf::Texture texFourBlock;

	sf::Sprite *spriteBackground;
	sf::Sprite *spriteField1;
	sf::Sprite *spriteField2;
	sf::Sprite *spriteMenuBut;

	sf::Sprite *sprOneBlock;
	sf::Sprite *sprTwoBlock;
	sf::Sprite *sprThreeBlock;
	sf::Sprite *sprFourBlock;

	sf::Texture texMicroMenu;
	sf::Sprite *sprMicroMenu;

	sf::Texture texContMicroMenuBut;
	sf::Texture texStopMicroMenuBut;
	sf::Texture texExitMicroMenuBut;

	sf::Sprite* sprContMicroMenuBut;
	sf::Sprite* sprStopMicroMenuBut;
	sf::Sprite* sprExitMicroMenuBut;

	sf::Texture texObjectsPoint;
	sf::Sprite *sprObjectPoint;
	sf::Texture texObjectsX;
	sf::Sprite *sprObjectX;

	sf::Texture texEndScreenWin0;
	sf::Texture texEndScreenWin1;
	sf::Texture texEndScreenWin2;

	sf::Sprite* sprEndScreenWin0;
	sf::Sprite* sprEndScreenWin1;
	sf::Sprite* sprEndScreenWin2;

public:
	Game();
	~Game();


	void setStartField();
	void setMainArea();
	void setBlocks();
	void setMicroMenuBut();
	void setEndScreenWin();

	void drawWinner(sf::RenderWindow* win);
    size_t getWinner(){ return winner;}
	size_t* getField1() { return Field1; }
	size_t* getField2() { return Field2; }
	bool getMustStopGame() { return mustStopGame; }
	void drawChosenShip(sf::RenderWindow* window,  sf::Vector2<float> pos, size_t horizontal);

	template<size_t numberPlayer>void drawShip(size_t type, sf::RenderWindow* window, size_t point){
	    sf::Sprite *field;
	    numberPlayer == 1 ? field = spriteField1 : field = spriteField2;
	    sf::Vector2<float> posField = field->getPosition();
	    sf::Vector2<float> posFieldNew(posField.x + 1 + Picture::LENGTH_ONE_CELL * (point % GameConst::LENGTH_FIELD_IN_CELLS),
                                       posField.y + 2 + Picture::LENGTH_ONE_CELL * (point / GameConst::LENGTH_FIELD_IN_CELLS));

	    if(type >= SHIP1 && type <= SHIP4){
	        sf::Sprite spr = *sprOneBlock;

	        spr.setPosition(posFieldNew);
	        window->draw(spr);
	    }

	    if(type == NEAR_SHIP){
	        sf::Sprite *spr = sprObjectPoint;

	        spr->setPosition(posFieldNew);
	        window->draw(*spr);
	    }
	}

	template <size_t numberPlayer>void drawSetShipsGame(sf::RenderWindow* window, size_t *field,  sf::Vector2<float> pos, size_t horizontal){
	    window->clear(sf::Color::White);


	    window->draw(*spriteBackground);
	    window->draw(*spriteField1);
	    window->draw(*spriteField2);
	    window->draw(*spriteMenuBut);
	    window->draw(*sprOneBlock);
	    window->draw(*sprTwoBlock);
	    window->draw(*sprThreeBlock);
	    window->draw(*sprFourBlock);


	    for(size_t i = 0; i < GameConst::AREA_FIELD; i++){
	        if(field[i] <= BROKEN && field[i] >= SHIP1){
	            drawShip<numberPlayer>(field[i], window, i);
	        }
	    }

	    if(typeSetBlock <= FOUR_BLOCK && typeSetBlock >= ONE_BLOCK){
	        drawChosenShip(window, pos, horizontal);
	    }

	    window->display();


	}

	template <size_t numberPlayer> void drawObject(size_t type, sf::RenderWindow* window, size_t point){
	    sf::Sprite *field;
	    numberPlayer == 1 ? field = spriteField1 : field = spriteField2;
	    sf::Vector2<float> posField = field->getPosition();
	    sf::Vector2<float> posFieldNew(posField.x + 2 + Picture::LENGTH_ONE_CELL * (point % GameConst::LENGTH_FIELD_IN_CELLS),
                                       posField.y + 2 + Picture::LENGTH_ONE_CELL * (point / GameConst::LENGTH_FIELD_IN_CELLS));

	    if(type == KILLED){
	        sf::Sprite *spr = sprOneBlock;

	        spr->setPosition(posFieldNew);
	        window->draw(*spr);
	    }
	    else if(type == BROKEN){
	        sf::Sprite *spr = sprObjectX;
	        spr->setPosition(posFieldNew);
	        window->draw(*spr);
	    }
	    else {
	        sf::Sprite *spr = sprObjectPoint;
	        spr->setPosition(posFieldNew);
	        window->draw(*spr);
	    }
	}

	void drawGame(sf::RenderWindow* window);

	bool checkNext(size_t next, const size_t *field, size_t typeWay);
	bool showMicroMenu(sf::RenderWindow* window);
	void setStandartColorMicroMenu(sf::RenderWindow* window);
	void setNearShip(size_t point,size_t sizeBlock, size_t* field, bool horizontal);
	void setShip(size_t point, size_t sizeBlock, size_t* field, bool horizontal);
	void killShips(size_t *field, size_t point);
	bool isNotAblessSet(size_t* field, size_t sizeBlock, size_t horizontal, size_t point);

	void fillingCage(size_t* field, size_t size, IGamer* player, sf::RenderWindow* window);

	template<size_t numberPlayer>  bool realPlayerFilling(IGamer* player, sf::RenderWindow * window){
	    size_t* field;
	    sf::Sprite *sprSelfField;
	    numberPlayer == 1 ?
	    (field = Field1,sprSelfField = spriteField1):
	    (field = Field2,sprSelfField = spriteField2);

	    bool horizontal = true;

	    while (window->isOpen()) {
	        setStandartColor(player);

	        sprSelfField->setColor(sf::Color::Red);

	        sf::Vector2<float> pos = (sf::Vector2<float>)sf::Mouse::getPosition(*window);
	        reaction = NOTHING;

	        if(sprOneBlock->getGlobalBounds().contains(pos.x, pos.y)){
	            reaction = ONE_BLOCK; }
	        if(sprTwoBlock->getGlobalBounds().contains(pos.x, pos.y)){
	             reaction = TWO_BLOCK; }
	        if(sprThreeBlock->getGlobalBounds().contains(pos.x, pos.y)){
	            reaction = THREE_BLOCK; }
	        if(sprFourBlock->getGlobalBounds().contains(pos.x, pos.y)){
	            reaction = FOUR_BLOCK;  }
	        if(spriteMenuBut->getGlobalBounds().contains(pos.x, pos.y)){
	            spriteMenuBut->setColor(sf::Color::Black); reaction = MENU; }

	        if(player->isReady()/* && reaction == START_GAME*/){
	            sf::sleep(sf::seconds(2));
	            break;
	        }


	        sf::Event ev;
	        while (window->pollEvent(ev)) {
	            if (ev.type == sf::Event::Closed) {
	                window->close();
	                return false;
	            }
	            if (ev.type == ev.MouseButtonReleased && ev.mouseButton.button == sf::Mouse::Left){
	                if(reaction <= FOUR_BLOCK && reaction >= ONE_BLOCK){
	                    isSet = true;
	                    typeSetBlock = reaction;
	                }
	                else if(reaction == MENU){
	                    if(showMicroMenu(window)) {return true;}
	                }
	            }
	            if (ev.type == ev.MouseButtonReleased && ev.mouseButton.button == sf::Mouse::Right){
	                horizontal = !horizontal;
	            }
	        }

	        size_t point = GameConst::RANDOM_MORE100;
	        if(isSet && sprSelfField->getGlobalBounds().contains(pos.x, pos.y) &&
	        sf::Mouse::isButtonPressed(sf::Mouse::Left)){
	            sf::Vector2<float> beginningField = sprSelfField->getPosition();
	            point = (int)(pos.x - beginningField.x - 2) / Picture::LENGTH_ONE_CELL
	                    + GameConst::LENGTH_FIELD_IN_CELLS * ((int)(pos.y - beginningField.y - 2) / Picture::LENGTH_ONE_CELL);
	        }//real isPoint

	        if(point != GameConst::RANDOM_MORE100){
	            size_t sizeBlock = typeSetBlock - ONE_BLOCK + 1;
	            if(!isNotAblessSet(field, sizeBlock, horizontal, point) && player->isHavePlacesForShips(typeSetBlock)){
	                setNearShip(point, sizeBlock, field, horizontal);
	                setShip(point, typeSetBlock - ONE_BLOCK + 1, field, horizontal);
	                player->addShip(typeSetBlock);
	            }

	        }

            drawSetShipsGame<numberPlayer>(window, field, pos, horizontal);

	    }
	    sprSelfField->setColor(sf::Color::White);
	    return true;
	}


    template<size_t numberPlayer> void setField(IGamer* player,
                                                sf::RenderWindow* window) {
        size_t* field;
        numberPlayer == 1 ? field = Field1 : field = Field2;

        if(player->getTypePlayer() == RND){
            for(size_t i = GameConst::COUNT_SHIPS4; i <=GameConst::COUNT_SHIPS1; i++){
               fillingCage(field, i, player, window);
            }
        }
        else{
            realPlayerFilling<numberPlayer>(player, window);
        }
    }

    void setStandartStepColor();
	void setStandartColor(IGamer* player);
	bool isKilledShip(size_t*  field, size_t point);
	size_t typeShip(size_t sizeBlock);

	template<size_t numberPlayer>  bool step(IGamer* player, sf::RenderWindow * window){
	    size_t* field;
	    sf::Sprite *sprEnemy;
	    numberPlayer == 1 ?
	        (field = Field2, sprEnemy = spriteField2) :
	        (field = Field1, sprEnemy = spriteField1);

	    while (window->isOpen()) {
	        setStandartStepColor();
	        sprEnemy->setColor(sf::Color::Red);

	        sf::Vector2<int> pos = sf::Mouse::getPosition(*window);
	        reaction = NOTHING;

	        size_t numCell = GameConst::RANDOM_MORE100;
	        size_t point = GameConst::RANDOM_MORE100;
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
            sprEnemy->getGlobalBounds().contains(pos.x, pos.y) &&
	        player->getTypePlayer() == REAL){
	            sf::Vector2<float> beginningField = sprEnemy->getPosition();
	            numCell = (pos.x - (int)beginningField.x - 2) / Picture::LENGTH_ONE_CELL
	                    + GameConst::LENGTH_FIELD_IN_CELLS *
	                    ((pos.y - (int)beginningField.y - 2) / Picture::LENGTH_ONE_CELL);
	        }//real isCell

	        if(player->isStep(
	                reaction, &point, numCell, field) &&
	                !(field[point]==BROKEN ||
	                field[point]== POINT ||
	                field[point] == KILLED))
	        {

	            if(field[point] >= SHIP1 && field[point] <= SHIP4){
	                player->breakShip(field, point);
	                if(isKilledShip(field, point)){
	                    if(player->lessShipsCount()){
	                        if(winner == NOTHING){
	                            winner = numberPlayer;
	                        }
	                        else{
	                            winner = NOTHING;
	                        }
	                        return false;
	                    }
	                }

	            }
	            else if(field[point] == BROKEN ||field[point] == POINT || field[point] == KILLED){ break; }
	            else{
	                field[point] = POINT;
	                break;
	            }
	        }

	        if(spriteMenuBut->getGlobalBounds().contains(pos.x, pos.y)){
	            spriteMenuBut->setColor(sf::Color::Black); reaction = MENU; }


	        sf::Event ev;
	        while (window->pollEvent(ev)) {
	            if (ev.type == sf::Event::Closed) {
	                window->close();
	                return false;
	            }
	            if (ev.type == sf::Event::MouseButtonPressed){
	                if(reaction == MENU){
                        if(showMicroMenu(window)) {
                            return true;}
                    }
	            }
	        }
            drawGame(window);
	        sprEnemy->setColor(sf::Color::White);
	    }
	    drawGame(window);
	    sprEnemy->setColor(sf::Color::White);
	    return true;
	}
};
