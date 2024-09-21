#include "card.h"

int main(){
	Card a(CARD_NAME_ACE, CARD_SUIT_CLUB), b(CARD_NAME_TEN, CARD_SUIT_HEART), c(CARD_NAME_KING, CARD_SUIT_SPADE);
	a.print(); std::cout << endl;
	Card::print(new Card[3] {a, b, c}, 3 );
	getchar();
	return 0;
}