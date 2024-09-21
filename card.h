/*
  	ICTU - LEVEL 1 - GROUP4
  	Object Oriented Programming - GROUP3
  	Section A
*/

#ifndef __CARDS_H__
#define __CARDS_H__

#define CARD_NAME_ACE 1
#define CARD_NAME_TWO 2
#define CARD_NAME_TREE 3
#define CARD_NAME_FOUR 4
#define CARD_NAME_FIVE 5
#define CARD_NAME_SIX 6
#define CARD_NAME_SEVEN 7
#define CARD_NAME_EIGHT 8
#define CARD_NAME_NINE 9
#define CARD_NAME_TEN 10
#define CARD_NAME_JACK 11
#define CARD_NAME_QUEEN 12
#define CARD_NAME_KING 13

#define CARD_SUIT_CLUB 1
#define CARD_SUIT_DIAMOND 2
#define CARD_SUIT_HEART 3
#define CARD_SUIT_SPADE 4

#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

class Card {
	private:
		int name, suit;
	public:
		static const char* Card_names[13];
		static const char Card_suits[4];
		Card(int n, int s): name(n), suit(s) {}
		Card(int arr[2]): name(arr[0]), suit(arr[1]) {}
		~Card(){}
   		int get_name() const { return name; }
		int get_suit() const { return suit; }
		void print(ostream& os = cout) {
			os << " _________ " << endl;
			os << "|  _____  |" << endl;
			os << "|" << Card_suits[suit -1] << "|     | |" << endl;
			os << "| | " << Card_names[name -1] << " | |" << endl;
			os << "| |     | |" << endl;
			os << "| |     | |" << endl;
			os << "| |_____|" << Card_suits[suit -1] << "|" << endl;
			os << "|_________|";
		}
		void print(int line, ostream& os = cout){
			switch(line){
				case 1: {
					os << " _________ "; break;
				}
				case 2: {
					os << "|  _____  |"; break;
				}
				case 3: {
					os << "|" << Card_suits[suit -1] << "|     | |"; break;
				}
				case 4: {
					os << "| | " << Card_names[name -1] << " | |"; break;
				}
				case 5: {
					os << "| |     | |"; break;
				}
				case 6: {
					os << "| |     | |"; break;
				}
				case 7: {
					os << "| |_____|" << Card_suits[suit -1] << "|"; break;
				}
				case 8: {
					os << "|_________|"; break;
				}
			}
		}
};

#endif