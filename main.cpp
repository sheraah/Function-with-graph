#include "Game.h"


int main() {
	srand(time(0));

	Game game({ 1000, 800 }, "Functions", 20);

	game.run();
}