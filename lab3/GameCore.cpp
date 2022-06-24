#include "GameCore.hpp"

GameCore::GameCore() {
    win = new sf::RenderWindow(sf::VideoMode(Picture::LENGTH_WINDOW, Picture::HEIGHT_WINDOW),
                               "BattleOfSea",
                               sf::Style::Close | sf::Style::Titlebar);
    win->setFramerateLimit(GameConst::MAX_FPS);

}

GameCore::~GameCore() {
    delete win;
    delete menu1, delete menu2, delete menu3,
    delete menu4, delete menu5, delete menu6,
    delete menuBg, delete startGameButton,
    delete exitGameButton;

}

void GameCore::loadImagesFromFolder(){
    menuTexture1.loadFromFile(Picture::REAL_BUT);
    menuTexture2.loadFromFile(Picture::SMART_BUT);
    menuTexture3.loadFromFile(Picture::STUPID_BUT);
    menuTexture4.loadFromFile(Picture::REAL_BUT);
    menuTexture5.loadFromFile(Picture::SMART_BUT);
    menuTexture6.loadFromFile(Picture::STUPID_BUT);
    menuStart.loadFromFile(Picture::START_MAIN_MENU);
    menuExit.loadFromFile(Picture::EXIT_MAIN_MENU);
    menuBackground.loadFromFile(Picture::BACKGROUND_MAIN_MENU);
}

void GameCore::setPositionSprites(){
    float butLenght1 = Picture::LENGTH_PLACE_CHOOSE_TYPE1;
    float butLenght2 = Picture::LENGTH_PLACE_CHOOSE_TYPE2;

    float butHeight = Picture::HEIGHT_PLACE_CHOOSE_TYPE;
    float shiftHeight = Picture::HEIGHT_PLACE_CHOOSE_TYPE / 2;

    float startLenght = (butLenght1 + butLenght2) * 0.5;
    float startHeight = butHeight + shiftHeight * 1.5;

    float exitLenght = Picture::LENGTH_WINDOW - Picture::HEIGHT_PLACE_CHOOSE_TYPE;
    float exitHeight = Picture::HEIGHT_PLACE_CHOOSE_TYPE / 2;

    menu1->setPosition(butLenght1, butHeight);
    menu2->setPosition(butLenght1, butHeight + shiftHeight);
    menu3->setPosition(butLenght1, butHeight + 2 * shiftHeight);
    menu4->setPosition(butLenght2, butHeight);
    menu5->setPosition(butLenght2, butHeight + shiftHeight);
    menu6->setPosition(butLenght2, butHeight + 2 * shiftHeight);

    startGameButton->setPosition(startLenght, startHeight);
    exitGameButton->setPosition(exitLenght, exitHeight);
    menu6->setPosition(butLenght2, butHeight + 2 * shiftHeight);
    menuBg->setPosition(0, 0);
}

void GameCore::setSpriteForImages(){
    menu1 = new sf::Sprite(menuTexture1);
    menu2 = new sf::Sprite(menuTexture2);
    menu3 = new sf::Sprite(menuTexture3);
    menu4 = new sf::Sprite(menuTexture4);
    menu5 = new sf::Sprite(menuTexture5);
    menu6 = new sf::Sprite(menuTexture6);
    menuBg = new sf::Sprite(menuBackground);
    startGameButton = new sf::Sprite(menuStart);
    exitGameButton = new sf::Sprite(menuExit);
    setPositionSprites();
}

void GameCore::showMenuGame() {
    win->clear();
    win->draw(*menuBg);
    win->draw(*menu1);
    win->draw(*menu2);
    win->draw(*menu3);
    win->draw(*menu4);
    win->draw(*menu5);
    win->draw(*menu6);
    win->draw(*startGameButton);
    win->draw(*exitGameButton);

    win->display();
}

void GameCore::setSpritesWhiteColor() {
    menu1->setColor(sf::Color::White);
    menu2->setColor(sf::Color::White);
    menu3->setColor(sf::Color::White);
    menu4->setColor(sf::Color::White);
    menu5->setColor(sf::Color::White);
    menu6->setColor(sf::Color::White);
    startGameButton->setColor(sf::Color::White);
    exitGameButton->setColor(sf::Color::White);
}

bool GameCore::menu(size_t* typeFirstPlayer, size_t* typeSecondPlayer) {
	loadImagesFromFolder();
    setSpriteForImages();

    bool isNotExit = true;
	bool isMenu = true;
	size_t menuNum;

	while (isMenu) {
	    sf::Event ev;
		while (win->pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				win->close();
				isNotExit = false;
				isMenu = false;
			}
		}

		setSpritesWhiteColor();
		menuNum = NOTHING;
		sf::Vector2<float> pos = (sf::Vector2<float>)sf::Mouse::getPosition(*win);

		if(*typeFirstPlayer == REAL1){menu1->setColor(sf::Color::Yellow);}
		if(*typeSecondPlayer == REAL2){menu4->setColor(sf::Color::Yellow);}
		if(*typeFirstPlayer == RND1){menu3->setColor(sf::Color::Yellow);}
		if(*typeSecondPlayer == RND2){menu6->setColor(sf::Color::Yellow);}
		if(*typeFirstPlayer == SMARTRND1){menu2->setColor(sf::Color::Yellow);}
		if(*typeSecondPlayer == SMARTRND2){menu5->setColor(sf::Color::Yellow);}


		if(menu1->getGlobalBounds().contains(pos.x, pos.y)){
		     menuNum = REAL1; }
		if(menu2->getGlobalBounds().contains(pos.x, pos.y)){
		     menuNum = SMARTRND1; }
		if(menu3->getGlobalBounds().contains(pos.x, pos.y)){
		     menuNum = RND1; }
		if(menu4->getGlobalBounds().contains(pos.x, pos.y)){
		     menuNum = REAL2; }
		if(menu5->getGlobalBounds().contains(pos.x, pos.y)){
		     menuNum = SMARTRND2; }
		if(menu6->getGlobalBounds().contains(pos.x, pos.y)){
		     menuNum = RND2; }

		if(startGameButton->getGlobalBounds().contains(pos.x, pos.y)){
		    startGameButton->setColor(sf::Color::Red); menuNum = START_GAME; }
		if(exitGameButton->getGlobalBounds().contains(pos.x, pos.y)){
		        exitGameButton->setColor(sf::Color::Green); menuNum = EXIT_GAME; }

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (menuNum == START_GAME) isMenu = false;
			else if (menuNum == EXIT_GAME) { isMenu = false; isNotExit = false; }
			else if (menuNum == RND1 ||
				menuNum == SMARTRND1 ||
				menuNum == REAL1) {
				*typeFirstPlayer = menuNum;
			}
			else if (menuNum == RND2 ||
				menuNum == SMARTRND2 ||
				menuNum == REAL2) {
				*typeSecondPlayer = menuNum;
			}
		}

		showMenuGame();
	}
	return isNotExit;
}


void GameCore::game(IGamer* player1, IGamer* player2) {
    Game g;
    sf::RenderWindow* window = getWin();

    g.setField<1>(player1, window);
    if(g.getMustStopGame()){ return; }
    g.setField<2>(player2, window);
    if(g.getMustStopGame()){ return; }
    bool isNotEnd = true;
    while(isNotEnd && window->isOpen()) {
        isNotEnd &= g.step<1>(player1, window);
        if(g.getMustStopGame()){
            break;
        }
        isNotEnd &= g.step<2>(player2, window);
        g.drawGame(window);
    }
    if(!g.getMustStopGame() && !isNotEnd){ g.drawWinner(window);}

}
