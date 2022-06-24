#pragma once
#include "game.hpp"


class GameCore{
private:
	sf::RenderWindow* win;
	sf::Texture menuTexture1, menuTexture2, menuTexture3, menuTexture4,
	menuTexture5, menuTexture6, menuBackground,
	menuStart, menuExit;
	sf::Sprite	*menu1, *menu2, *menu3,
	*menu4, *menu5, *menu6,
	*menuBg, *startGameButton,
	*exitGameButton;


public:
	GameCore();
	~GameCore();
	bool menu(size_t* typeFirstPlayer, size_t* typeSecondPlayer);
	sf::RenderWindow* getWin() { return win; }
	void setPositionSprites();
	void setSpritesWhiteColor();
	void loadImagesFromFolder();
	void setSpriteForImages();
	void showMenuGame();
	void game(IGamer* player1, IGamer* player2);
};
