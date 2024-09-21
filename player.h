/*
  	ICTU - LEVEL 1 - GROUP4
  	Object Oriented Programming - GROUP3
  	Section B
*/

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "card.h"
#include <string>
#include <ctime>
#include <vector>
using std::istream;
using std::cin;
using std::string;
using std::vector;

class Player {
	protected:
		int number;
		string password;
		bool turn;
		bool is_playing;
		int score;
		Card* hand;
	public:
		Player(	int num, string pass,
				int cn1, int cs1,
				int cn2, int cs2,
				int cn3, int cs3):
				number(num), password(pass), is_playing(true), score(0), turn(false)
				{ hand = new Card[3] { Card(cn1, cs1), Card(cn2, cs2), Card(cn3, cs3)}; }
		virtual ~Player() {}
		
		int* get_card(int i) const {
			if(i >= 0 and i <= 2) return new int[2] { hand[i].get_name(), hand[i].get_suit() };
			else return NULL;
		}
		
		bool isPlaying() const { return is_playing; }
		int get_score() const { return score; }
		void set_score(int s) { if(turn) score = s;}
		void add_score(int s) { if(turn) score += s;}
		
		void begin_turn(ostream& os = cout, istream& is = cin) {
			string tmp;
			os << "Player " << number << endl;
			do{
				os << "Enter your pass phrase : ";
				is >> tmp;
				if(tmp == password) turn = true;
			}while(turn == false);
		}
		void displayscore(ostream& os = cout) { if(turn) os << "Your Score : " << score << endl; }
		void displaycards(ostream& os = cout){
			if(not turn) return;
			
			os << "Your Hand" << endl;
			for(int i = 0; i < 8; i++) {
				hand[0].print(i+1, os); os << '\t';
				hand[1].print(i+1, os); os << '\t';
				hand[2].print(i+1, os); os << endl;
			}
		}
		void end_turn() {
			turn = false;
			system("cls");
		}
		void game_over() {
			is_playing = false;
			turn = true;
		}
};

template <class PlayerType>
class GameProvider {
	protected:
		int num_players;
		vector<PlayerType> players;
		int winner, temp_winner;
	public:
		GameProvider(istream& is = cin, ostream& os = cout): 
		winner(0), temp_winner(0), players() {
			os << "How many Players ? (max 4)" << endl;
			is >> num_players;
			num_players = num_players < 0 ? 2 : num_players;
			num_players = num_players > 4 ? 4 : num_players;
			num_players++;										// Plus one for PC
			system("cls");
			
			srand((unsigned int) time(0));
			for(int i = 0; i < num_players; i++){
				string tmp;
				if(i == 0) tmp = "PC";
				else {
					os << "Player " << i << " password : ";
					is >> tmp;
				}
				PlayerType* new_player = new PlayerType(i, tmp, 1 +(rand() % 13), 1 +(rand() % 4), 1 +(rand() % 13), 1 +(rand() % 4), 1 +(rand() % 13), 1 +(rand() % 4));
				players.push_back(*new_player);
				system("cls");
			}
		}
		virtual ~GameProvider() {}
		void new_game(istream& is = cin, ostream& os = cout) {
			os << "How many Players ? (max 4)" << endl;
			is >> num_players;
			num_players = num_players < 0 ? 2 : num_players;
			num_players = num_players > 4 ? 4 : num_players;
			num_players++;										// Plus one for PC
			system("cls");
			
			srand((unsigned int) time(0));
			players.clear();
			for(int i = 0; i < num_players; i++){
				string tmp;
				if(i == 0) tmp = "PC";
				else {
					os << "Player " << i << " password : ";
					is >> tmp;
				}
				PlayerType* new_player = new PlayerType(i, tmp, 1 +(rand() % 13), 1 +(rand() % 4), 1 +(rand() % 13), 1 +(rand() % 4), 1 +(rand() % 13), 1 +(rand() % 4));
				players.push_back(*new_player);
				system("cls");
			}
		}
		
		int count_rem_players() {
			int result = 0;
			for(int i = 1; i < num_players; i++)
				if(players[i].isPlaying()) result++;
			return result;
		}
		
		virtual void player_turn(int p_num, istream& is = cin, ostream& os = cout) {
			PlayerType* player = &players[p_num];
			if(not player->isPlaying()) return;
			player->begin_turn(os, is);
			player->displayscore(os);
			player->displaycards(os);
			os 	<< "What do you want?" << endl
				<< "(C)ontinue" << endl
				<< "(A)bort" << endl;
			char choice;
			is >> choice;
			switch(choice) {
				case 'C' : case 'c' : {
					player->add_score(rand() % 10);	// Here is just an example of what we can do
					player->displayscore(os);
					os << "Press enter to finish your turn" << endl;
					getchar(); getchar();
 					player->end_turn();
					break;
				}
				case 'A': case 'a': {
					os << "Do you realy want to give up? (Y)es or anything else to cancel" << endl;
					char tmp;
					is >> tmp;
					if(tmp == 'Y' or tmp == 'y') {
						player->game_over();
						if(count_rem_players() == 1) evaluate_winner(true);
					}
					break;
				}
				default : {
					player->end_turn();
					break;
				}
			}
		}
		
		virtual void evaluate_winner(bool assign = false) {
			// Here is just an example (that could be overwritten)
			// In the basic situation, the winner of the
			// game is the one with he highest score
			// Winner equals zero means draw
			int max_score = -1; // That way, the counter will initialise with player1's score
			for(int i = 1; i < num_players; i++) {
				if(not players[i].isPlaying()) continue;
				if(players[i].get_score() > max_score) { max_score = players[i].get_score(); temp_winner = i; }
				else if(players[i].get_score() == max_score) temp_winner = 0;
			}
			winner = assign ? temp_winner : winner;
		}
		
		virtual bool should_game_continue() {
			// Here also is just an example (that should be overwritten)
			// We decide to stop the game when a player the reach a certain score
			if(count_rem_players() == 1) {
				evaluate_winner(true);
				return false;
			}
			const int limit = 30;
			for(int i = 1; i < num_players; i++)
			if(players[i].get_score() > limit) {
				evaluate_winner(true);
				return false;
			}
			return true;
		}
		
		bool terminate_game(istream& is = cin, ostream& os = cout) {
			os << "Game over" << endl;
			for(int i = 1; i < num_players; i++){
				players[i].game_over();
				os << "Player " << i << " score : " << players[i].get_score()<< endl;
				players[i].displaycards(os);
				os << endl;
			}
			if(winner > 0) os << "Winner : Player " << winner << endl << endl;
			else os << "Draw" << endl << endl;
			
			char r;
			os << "Do you want another round? (Y)es or anything else to finish : ";
			is >> r;
			system("cls");
			if(r == 'Y' or r =='y') return false;
			else return true;
		}
		virtual void game_loop(){
			do {
				do { for(int i = 1; i < num_players; i++) player_turn(i); }
				while(should_game_continue());
				if(terminate_game()) break;
				new_game();
			}while(true);
		}
};

#endif