#include "game.hpp"


void Game::setStartField() {
    Field1 = new size_t[GameConst::AREA_FIELD];
    Field2 = new size_t[GameConst::AREA_FIELD];

    for (size_t i = 0; i < GameConst::AREA_FIELD; i++) {
        Field1[i] = EMPTY;
        Field2[i] = EMPTY;
    }
}

void Game::setMainArea() {
    background.loadFromFile(Picture::BACKGROUND);
    field1.loadFromFile(Picture::FIELD);
    field2.loadFromFile(Picture::FIELD);
    menuBut.loadFromFile(Picture::MENU);

    spriteBackground = new sf::Sprite(background);
    spriteField1 = new sf::Sprite(field1);
    spriteField2 = new sf::Sprite(field2);
    spriteMenuBut = new sf::Sprite(menuBut);

    spriteField1->setPosition(Picture::LENGTH_FIELD_LEFT1,
                              Picture::HEIGHT_FIELD_LEFT);
    spriteField2->setPosition(Picture::LENGTH_FIELD_LEFT2,
                              Picture::HEIGHT_FIELD_LEFT);
    spriteMenuBut->setPosition(Picture::LENGTH_WINDOW - Picture::LENGTH_MENU_BUT_IN_GAME, 0);
}

void Game::setBlocks() {
    texObjectsPoint.loadFromFile(Picture::POINT);
    texObjectsX.loadFromFile(Picture::X);
    sprObjectPoint = new sf::Sprite(texObjectsPoint);
    sprObjectX = new sf::Sprite(texObjectsX);


    texOneBlock.loadFromFile(Picture::BLOCK1);
    texTwoBlock.loadFromFile(Picture::BLOCK2);
    texThreeBlock.loadFromFile(Picture::BLOCK3);
    texFourBlock.loadFromFile(Picture::BLOCK4);

    sprOneBlock = new sf::Sprite(texOneBlock);
    sprTwoBlock = new sf::Sprite(texTwoBlock);
    sprThreeBlock = new sf::Sprite(texThreeBlock);
    sprFourBlock = new sf::Sprite(texFourBlock);

    sprOneBlock->setPosition(Picture::LENGTH_SETS_BLOCKS, Picture::HEIGHT_SETS_BLOCKS);
    sprTwoBlock->setPosition(Picture::LENGTH_SETS_BLOCKS + 2 * Picture::LENGTH_ONE_CELL, Picture::HEIGHT_SETS_BLOCKS);
    sprThreeBlock->setPosition(Picture::LENGTH_SETS_BLOCKS + (2 + 3) * Picture::LENGTH_ONE_CELL, Picture::HEIGHT_SETS_BLOCKS);
    sprFourBlock->setPosition(Picture::LENGTH_SETS_BLOCKS + (2 + 3 + 4) * Picture::LENGTH_ONE_CELL, Picture::HEIGHT_SETS_BLOCKS);


}

void Game::setMicroMenuBut() {
    texMicroMenu.loadFromFile(Picture::MICRO_MENU);;
    sprMicroMenu = new sf::Sprite(texMicroMenu);
    sprMicroMenu->setPosition(Picture::LENGTH_PLACE_MICRO_MENU_BUT - Picture::SHIFT_BETW_MIC_MEN_AND_BUTTONS,
                              Picture::HEIGHT_MICRO_MENU);

    texContMicroMenuBut.loadFromFile(Picture::CONTINUE_GAME);
    texStopMicroMenuBut.loadFromFile(Picture::STOP_GAME);
    texExitMicroMenuBut.loadFromFile(Picture::EXIT_GAME);

    sprContMicroMenuBut = new sf::Sprite(texContMicroMenuBut);
    sprStopMicroMenuBut = new sf::Sprite(texStopMicroMenuBut);
    sprExitMicroMenuBut = new sf::Sprite(texExitMicroMenuBut);

    sprContMicroMenuBut->setPosition(Picture::LENGTH_PLACE_MICRO_MENU_BUT,
                                     Picture::HEIGHT_PLACE_MICRO_MENU_BUT);
    sprStopMicroMenuBut->setPosition(Picture::LENGTH_PLACE_MICRO_MENU_BUT,
                                     Picture::HEIGHT_PLACE_MICRO_MENU_BUT + Picture::SHIFT_BETW_MIC_MEN_BUT);
    sprExitMicroMenuBut->setPosition(Picture::LENGTH_PLACE_MICRO_MENU_BUT,
                                     Picture::HEIGHT_PLACE_MICRO_MENU_BUT + 2 * Picture::SHIFT_BETW_MIC_MEN_BUT);

}

void Game::setEndScreenWin() {
    texEndScreenWin0.loadFromFile(Picture::END_SCREEN0 );
    texEndScreenWin1.loadFromFile(Picture::END_SCREEN1);
    texEndScreenWin2.loadFromFile(Picture::END_SCREEN2);


    sprEndScreenWin0 = new sf::Sprite(texEndScreenWin0);
    sprEndScreenWin1 = new sf::Sprite(texEndScreenWin1);
    sprEndScreenWin2 = new sf::Sprite(texEndScreenWin2);

    sprEndScreenWin0->setPosition(Picture::LENGTH_PLACE_END_SCREEN,
                                  Picture::HEIGHT_PLACE_END_SCREEN);
    sprEndScreenWin1->setPosition(Picture::LENGTH_PLACE_END_SCREEN,
                                  Picture::HEIGHT_PLACE_END_SCREEN);
    sprEndScreenWin2->setPosition(Picture::LENGTH_PLACE_END_SCREEN,
                                  Picture::HEIGHT_PLACE_END_SCREEN);

    sf::Color color(255,255,255,256 * 0.5);
    sprEndScreenWin0->setColor(color);
    sprEndScreenWin1->setColor(color);
    sprEndScreenWin2->setColor(color);
}

Game::Game() {
	reaction = NOTHING;
	isSet = false;
	typeSetBlock = 0;
	winner = 0;
	mustStopGame = false;

    setStartField();
    setMainArea();
	setBlocks();
	setMicroMenuBut();
	setEndScreenWin();
}

Game::~Game() {
	delete[]Field1;
	delete[]Field2;

	delete spriteBackground;
	delete spriteField1;
	delete spriteField2;
	delete spriteMenuBut;

	delete sprOneBlock;
	delete sprTwoBlock;
	delete sprThreeBlock;
	delete sprFourBlock;

	delete sprMicroMenu;

	delete sprContMicroMenuBut;
	delete sprStopMicroMenuBut;
	delete sprExitMicroMenuBut;

	delete sprObjectPoint;
	delete sprObjectX;

	delete sprEndScreenWin0;
	delete sprEndScreenWin1;
	delete sprEndScreenWin2;
}

void Game::drawChosenShip(sf::RenderWindow* window,  sf::Vector2<float> pos, size_t horizontal){
    sf::Sprite spr;
    if(typeSetBlock == ONE_BLOCK){
        spr = *sprOneBlock;
    }
    else if(typeSetBlock == TWO_BLOCK){
        spr = *sprTwoBlock;
    }
    else if(typeSetBlock == THREE_BLOCK){
        spr = *sprThreeBlock;
    }
    else if(typeSetBlock == FOUR_BLOCK){
        spr = *sprFourBlock;
    }
    if(!horizontal){
        spr.setRotation(Picture::RIGHT_ANGLE);
    }
    spr.setOrigin(Picture::LENGTH_ONE_CELL / 2, Picture::LENGTH_ONE_CELL / 2);
    spr.setPosition(pos);
    window->draw(spr);
}

void Game::drawGame(sf::RenderWindow* window){
    window->clear(sf::Color::White);

    window->draw(*spriteBackground);
    window->draw(*spriteField1);
    window->draw(*spriteField2);
    window->draw(*spriteMenuBut);
    for(size_t i = 0; i < GameConst::AREA_FIELD; i++){
        if(Field1[i] <= KILLED && Field1[i] >= POINT){
            drawObject<1>(Field1[i], window, i);
        }
    }

    for(size_t i = 0; i < GameConst::AREA_FIELD; i++){
        if(Field2[i] <= KILLED && Field2[i] >= POINT){
            drawObject<2>(Field2[i], window, i);
        }
    }

    window->display();
}

void Game::drawWinner(sf::RenderWindow* win){
    while(win->isOpen()){

        sf::Event ev;
        while (win->pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                win->close();
            }
            if (ev.type == sf::Event::KeyPressed ){
                switch ( ev.key.code ) {
                    case sf::Keyboard::Enter:
                        return;
                    case sf::Keyboard::Escape:
                        return;
                }
            }

        }


        win->clear(sf::Color::White);

        win->draw(*spriteBackground);
        win->draw(*spriteField1);
        win->draw(*spriteField2);
        win->draw(*spriteMenuBut);
        for(size_t i = 0; i < GameConst::AREA_FIELD; i++){
            if(Field1[i] <= KILLED && Field1[i] >= POINT){
                drawObject<1>(Field1[i], win, i);
            }
        }

        for(size_t i = 0; i < GameConst::AREA_FIELD; i++){
            if(Field2[i] <= KILLED && Field2[i] >= POINT){
                drawObject<2>(Field2[i], win, i);
            }
        }


        if(winner == NOTHING){ win->draw(*sprEndScreenWin0);}
        else if(winner == 1){ win->draw(*sprEndScreenWin1);}
        else if(winner == 2){ win->draw(*sprEndScreenWin2);}


        win->display();
    }
}

void Game::setStandartColorMicroMenu(sf::RenderWindow* window){
    sprContMicroMenuBut->setColor(sf::Color::White);
    sprStopMicroMenuBut->setColor(sf::Color::White);
    sprExitMicroMenuBut->setColor(sf::Color::White);
}

bool Game::showMicroMenu(sf::RenderWindow* window){
    while(true){
        setStandartColorMicroMenu(window);
        sf::Vector2<int> pos = sf::Mouse::getPosition(*window);
        sf::Color colorPressed(90,90,90);
        reaction = NOTHING;

        if(sprContMicroMenuBut->getGlobalBounds().contains(pos.x, pos.y)){
            sprContMicroMenuBut->setColor(colorPressed); reaction = CONTINUE_MICRO_MENU; }
        if(sprStopMicroMenuBut->getGlobalBounds().contains(pos.x, pos.y)){
            sprStopMicroMenuBut->setColor(colorPressed); reaction = STOP_MICRO_MENU; }
        if(sprExitMicroMenuBut->getGlobalBounds().contains(pos.x, pos.y)){
            sprExitMicroMenuBut->setColor(colorPressed); reaction = EXIT_MICRO_MENU; }

        sf::Event ev;
        while (window->pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                window->close();
            }
            if (ev.type == sf::Event::MouseButtonPressed){
                if(reaction == CONTINUE_MICRO_MENU){
                    return false;
                }
                else if(reaction == STOP_MICRO_MENU){
                    mustStopGame = true;
                    return true;}
                else if(reaction == EXIT_MICRO_MENU){
                        window->close();
                        return true;}
                }
        }

        window->clear();

        window->draw(*spriteBackground);
        window->draw(*sprMicroMenu);
        window->draw(*sprContMicroMenuBut);
        window->draw(*sprStopMicroMenuBut);
        window->draw(*sprExitMicroMenuBut);

        window->display();
    }
}

bool checkAblessSet(size_t* field,size_t sizeBlock,bool horizontal, size_t point){
    for(size_t i = 0; i < sizeBlock; i++){
        size_t next = point + pow(GameConst::LENGTH_FIELD_IN_CELLS, (size_t)(!horizontal)) * i;
        if(field[next] >= SHIP1 && field[next] <= NEAR_SHIP){
            return false;
        }
    }
    return true;
}

bool isJump(size_t sizeBlock, size_t point, size_t horizontal){
    if(horizontal){
        return point % GameConst::LENGTH_FIELD_IN_CELLS > GameConst::LENGTH_FIELD_IN_CELLS - sizeBlock;
    }
    else{
        return point >= GameConst::LENGTH_FIELD_IN_CELLS * (GameConst::LENGTH_FIELD_IN_CELLS + 1 - sizeBlock);
    }
}

void check_setBorder(size_t* field, size_t point){
    bool isUp = true;
    bool isDown = true;
    bool isRight = true;
    bool isLeft = true;

    if(point % GameConst::LENGTH_FIELD_IN_CELLS == 0){
        isLeft = false;
    } else field[point - 1] = NEAR_SHIP;
    if(point % GameConst::LENGTH_FIELD_IN_CELLS == GameConst::LENGTH_FIELD_IN_CELLS - 1){
        isRight = false;
    } else field[point + 1] = NEAR_SHIP;
    if(point / GameConst::LENGTH_FIELD_IN_CELLS == 0){
        isUp = false;
    } else field[point - GameConst::LENGTH_FIELD_IN_CELLS] = NEAR_SHIP;
    if(point / GameConst::LENGTH_FIELD_IN_CELLS == GameConst::LENGTH_FIELD_IN_CELLS - 1){
        isDown = false;
    } else field[point + GameConst::LENGTH_FIELD_IN_CELLS] = NEAR_SHIP;

    if(isUp && isRight){
        field[point - GameConst::LENGTH_FIELD_IN_CELLS + 1] = NEAR_SHIP; }
    if(isDown && isRight){
        field[point + GameConst::LENGTH_FIELD_IN_CELLS + 1] = NEAR_SHIP; }
    if(isUp && isLeft){
        field[point - GameConst::LENGTH_FIELD_IN_CELLS - 1] = NEAR_SHIP; }
    if(isDown && isLeft){
        field[point + GameConst::LENGTH_FIELD_IN_CELLS - 1] = NEAR_SHIP; }
}

void Game::setNearShip(size_t point, size_t sizeBlock, size_t* field, bool horizontal){
    for(size_t j = 0; j < sizeBlock; j++){
        size_t next = point + j * (size_t)pow(GameConst::LENGTH_FIELD_IN_CELLS, (int)(!horizontal));
        check_setBorder(field, next);
    }
}

int takeShift(const size_t typeWay){
    int length = GameConst::LENGTH_FIELD_IN_CELLS;
    if(typeWay == LEFT){return -1;}
    else if(typeWay == RIGHT){return 1;}
    else if(typeWay == UP){return -length;}
    else {return length;}
}

int takeInverseShift(const size_t typeWay){
    if(typeWay == LEFT || typeWay == RIGHT){return GameConst::LENGTH_FIELD_IN_CELLS;}
    else {return 1;}
}


bool Game::checkNext(size_t point, const size_t* field, size_t typeWay){
    int shift = takeShift(typeWay);

    size_t next = (int)point + shift;
    bool is2 = true;
    for(int i = 0; i < 3 && is2; i++, next = (int)next + shift){
        is2 = checkWays(typeWay, next);
        if(field[next] == BROKEN){
            continue;
        }
        else if(field[next] == POINT || field[next] == EMPTY||field[next] == NEAR_SHIP){
            return false;
        }
        else{
            return true;
        }
    }
    return false;
}


void setPointsNearlyCell(size_t* field, size_t point){
    bool isUp = true;
    bool isDown = true;
    bool isRight = true;
    bool isLeft = true;

    if(point % GameConst::LENGTH_FIELD_IN_CELLS == 0){ isLeft = false; }
    if(point % GameConst::LENGTH_FIELD_IN_CELLS == GameConst::LENGTH_FIELD_IN_CELLS - 1){ isRight = false; }
    if(point / GameConst::LENGTH_FIELD_IN_CELLS == 0){ isUp = false; }
    if(point / GameConst::LENGTH_FIELD_IN_CELLS == GameConst::LENGTH_FIELD_IN_CELLS - 1){ isDown = false; }

    if(isUp && field[point - GameConst::LENGTH_FIELD_IN_CELLS ] == NEAR_SHIP){ field[point - GameConst::LENGTH_FIELD_IN_CELLS] = POINT; }
    if(isDown  && field[point + GameConst::LENGTH_FIELD_IN_CELLS ] == NEAR_SHIP){ field[point + GameConst::LENGTH_FIELD_IN_CELLS ] = POINT; }
    if(isLeft && field[point - 1]== NEAR_SHIP){ field[point - 1] = POINT; }
    if(isRight && field[point + 1]== NEAR_SHIP){ field[point + 1] = POINT; }

    if(isUp && isRight && field[point - GameConst::LENGTH_FIELD_IN_CELLS + 1] == NEAR_SHIP){ field[point - GameConst::LENGTH_FIELD_IN_CELLS + 1] = POINT; }
    if(isDown && isRight && field[point + GameConst::LENGTH_FIELD_IN_CELLS + 1] == NEAR_SHIP){ field[point + GameConst::LENGTH_FIELD_IN_CELLS + 1] = POINT; }
    if(isUp && isLeft && field[point - GameConst::LENGTH_FIELD_IN_CELLS - 1] == NEAR_SHIP){ field[point - GameConst::LENGTH_FIELD_IN_CELLS - 1] = POINT; }
    if(isDown && isLeft && field[point + GameConst::LENGTH_FIELD_IN_CELLS - 1] == NEAR_SHIP){ field[point + GameConst::LENGTH_FIELD_IN_CELLS - 1] = POINT; }
}

void killWay(size_t point,size_t* field, size_t direction){
    int shift = takeShift(direction);
    int inverseShift = takeInverseShift(direction);
    if(checkWays(direction, point)){
        size_t next = (int)point + shift;
        for(int i = 0; i < 3; i++, next = (int)next + shift){
            if(checkWays(direction, (int)next - shift) && field[next] == BROKEN){
                setPointsNearlyCell(field, next);
                field[next] = KILLED;
            }
            else {break;}
        }
    }

}

void Game::killShips(size_t *field, size_t point){
    killWay(point, field, LEFT);
    killWay(point, field, RIGHT);
    killWay(point, field, UP);
    killWay(point, field, DOWN);
    setPointsNearlyCell(field, point);
    field[point] = KILLED;
}

bool Game::isKilledShip(size_t *field, size_t point){
    if(point % GameConst::LENGTH_FIELD_IN_CELLS != 0){//isLeft
        if(checkNext(point, field, LEFT)){
            return false;
        }
    }
    if(point % GameConst::LENGTH_FIELD_IN_CELLS != GameConst::LENGTH_FIELD_IN_CELLS - 1){//isRight
        if(checkNext(point, field, RIGHT)){
            return false;
        }
    }
    if(point / GameConst::LENGTH_FIELD_IN_CELLS != 0){//isUp
        if(checkNext(point, field, UP)){
            return false;
        }
    }
    if(point / GameConst::LENGTH_FIELD_IN_CELLS != GameConst::LENGTH_FIELD_IN_CELLS - 1){//isDown
        if(checkNext(point, field, DOWN)){
            return false;
        }
    }

    killShips(field, point);
    return true;
}

void Game:: setShip(size_t point, size_t sizeBlock, size_t* field, bool horizontal){
    for(size_t j = 0; j < sizeBlock; j++){
        size_t next = point + pow(GameConst::LENGTH_FIELD_IN_CELLS, (size_t)(!horizontal)) * j;
        field[next] = typeShip(sizeBlock);
    }
}

bool Game::isNotAblessSet(size_t* field, size_t sizeBlock, size_t horizontal, size_t point){
    return isJump(sizeBlock, point, horizontal) ||
    !checkAblessSet(field, sizeBlock, horizontal, point);
}

void Game::fillingCage(size_t* field, size_t size, IGamer* player, sf::RenderWindow* window){
    size_t sizeBlock =  GameConst::COUNT_SHIPS1 - size + 1;

    for(int i = 0; i < size; i++){
        while(true){
            size_t point = rand() % GameConst::AREA_FIELD;
            bool horizontal = rand() % 2;
            if (field[point] == EMPTY){
                if(isNotAblessSet(field, sizeBlock, horizontal, point)){continue;}
                setNearShip(point, sizeBlock, field, horizontal);
                setShip(point, sizeBlock, field, horizontal);
                break;
            }
        }
    }
}

void Game::setStandartStepColor(){
    sf::Color mainColorMenu(0, 0, 0, 128);
    spriteMenuBut->setColor(mainColorMenu);
}

void Game::setStandartColor(IGamer* player){
    sf::Color mainColorMenu(0, 0, 0, 128);
    spriteMenuBut->setColor(mainColorMenu);

    sprOneBlock->setColor(sf::Color::White);
    sprTwoBlock->setColor(sf::Color::White);
    sprThreeBlock->setColor(sf::Color::White);
    sprFourBlock->setColor(sf::Color::White);
    if(player->isAllShipsType(1)){sprOneBlock->setColor(mainColorMenu);}
    if(player->isAllShipsType(2)){sprTwoBlock->setColor(mainColorMenu);}
    if(player->isAllShipsType(3)){sprThreeBlock->setColor(mainColorMenu);}
    if(player->isAllShipsType(4)){sprFourBlock->setColor(mainColorMenu);}
}

size_t Game::typeShip(size_t sizeBlock){
    if(sizeBlock == 1){ return SHIP1; }
    else if(sizeBlock == 2){ return SHIP2; }
    else if(sizeBlock == 3){ return SHIP3; }
    else { return SHIP4; }
}
