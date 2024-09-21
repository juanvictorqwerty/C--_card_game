/*
  	ICTU - LEVEL 1 - GROUP4
  	Object Oriented Programming - GROUP3
  	Section A
*/

#ifndef __CARDS_H__
#define __CARDS_H__

#define CARD_NAME_ACE 13
#define CARD_NAME_TWO 1
#define CARD_NAME_TREE 2
#define CARD_NAME_FOUR 3
#define CARD_NAME_FIVE 4
#define CARD_NAME_SIX 5
#define CARD_NAME_SEVEN 6
#define CARD_NAME_EIGHT 7
#define CARD_NAME_NINE 8
#define CARD_NAME_TEN 9
#define CARD_NAME_JACK 10
#define CARD_NAME_QUEEN 11
#define CARD_NAME_KING 12

#define CARD_SUIT_CLUB 1
#define CARD_SUIT_DIAMOND 2
#define CARD_SUIT_HEART 3
#define CARD_SUIT_SPADE 4

#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

struct cardShort {
	int name;
	int suit;
};

class Card {
	private:
		int name, suit;
	public:
		static const char* Card_names[13];
		static const char Card_suits[4];
		Card(int n, int s): name(n), suit(s) {}
		Card(cardShort cshort): name(cshort.name), suit(cshort.suit) {}
		~Card(){}
   		int get_name() const { return name; }
		int get_suit() const { return suit; }
		void print() {
			cout << " _________ " << endl;
			cout << "|  _____  |" << endl;
			cout << "|" << Card_suits[suit -1] << "|     | |" << endl;
			cout << "| | " << Card_names[name -1] << " | |" << endl;
			cout << "| |     | |" << endl;
			cout << "| |     | |" << endl;
			cout << "| |_____|" << Card_suits[suit -1] << "|" << endl;
			cout << "|_________|";
		}
		void print(int line){
			switch(line){
				case 1: {
					cout << " _________ "; break;
				}
				case 2: {
					cout << "|  _____  |"; break;
				}
				case 3: {
					cout << "|" << Card_suits[suit -1] << "|     | |"; break;
				}
				case 4: {
					cout << "| | " << Card_names[name -1] << " | |"; break;
				}
				case 5: {
					cout << "| |     | |"; break;
				}
				case 6: {
					cout << "| |     | |"; break;
				}
				case 7: {
					cout << "| |_____|" << Card_suits[suit -1] << "|"; break;
				}
				case 8: {
					cout << "|_________|"; break;
				}
			}
		}
		static void print(Card* arr, int num) {
			for(int i = 0; i < 8; i++){
				for(int j = 0; j < num; j++) {
					arr[j].print(i+1);
					cout << '\t';
				}
				cout << endl;
			}
		}
		static bool Less(Card c1, Card c2) { return c1.name < c1.name; }
		static bool LessShort(cardShort c1, cardShort c2) { return c1.name < c2.name; }
};

const char* Card::Card_names[] = {
			" 2 ", " 3 ", " 4 ", " 5 ",
			" 6 ", " 7 ", " 8 ", " 9 ", "1 0",
			" J ", " Q ", " K ", "ACE"
		};
const char Card::Card_suits[] = { 'C', 'D', 'H', 'S'};

#endif