#include "card.h"

const char* Card::Card_names[] = {
			"ACE", " 2 ", " 3 ", " 4 ", " 5 ",
			" 6 ", " 7 ", " 8 ", " 9 ", "1 0",
			" J ", " Q ", " K "
		};
const char Card::Card_suits[] = { 'C', 'D', 'H', 'S'};

int main(){
	getchar();
	Card a(CARD_NAME_ACE, CARD_SUIT_DIAMOND), b(CARD_NAME_TEN, CARD_SUIT_HEART), c(CARD_NAME_KING, CARD_SUIT_SPADE);
	a.print(); std::cout << endl;
	for(int i = 0; i < 8; i++){
		a.print(i+1); std::cout << '\t'; b.print(i+1); std::cout << '\t'; c.print(i+1); std::cout << endl;
	}
	getchar();
	return 0;
}