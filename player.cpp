#include "player.h"
const char* Card::Card_names[] = {
			"ACE", " 2 ", " 3 ", " 4 ", " 5 ",
			" 6 ", " 7 ", " 8 ", " 9 ", "1 0",
			" J ", " Q ", " K "
		};
const char Card::Card_suits[] = { 'C', 'D', 'H', 'S'};

int main(){
	GameProvider<Player> game;
	game.game_loop();
	return 0;
}