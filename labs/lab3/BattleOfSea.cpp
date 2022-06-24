#include "GameCore.hpp"


IGamer* createPlayer(size_t type) {
    IGamer* n;
	if (type == SMARTRND1 || type == SMARTRND2) { n = new SmartBot(); }
	else if (type == REAL1 || type == REAL2) { n = new RealPlayer(); }
	else{ n = new StupidBot(); }
	return n;
}

int main(){
    srand(clock());

	GameCore w;
	size_t typeFirstPlayer = RND1;
	size_t typeSecondPlayer = RND2;

	while ( w.getWin()->isOpen() && w.menu(&typeFirstPlayer, &typeSecondPlayer) ) {
		IGamer* First = createPlayer(typeFirstPlayer);
		IGamer* Second = createPlayer(typeSecondPlayer);

		w.game(First, Second);
		delete First;
		delete Second;
		sf::sleep(sf::milliseconds(400));
	}

 	return 0;
}
