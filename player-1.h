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
#include <algorithm>
#include <random>
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
				cardShort c1,
				cardShort c2,
				cardShort c3):
				number(num), password(pass), is_playing(true), score(0), turn(false)
				{ hand = new Card[3] { Card(c1), Card(c2), Card(c3)}; }
		virtual ~Player() {}
		
		int* get_card(int i) const {
			if(i >= 0 and i <= 2) return new int[2] { hand[i].get_name(), hand[i].get_suit() };
			else return NULL;
		}
		
		bool isPlaying() const { return is_playing; }
		int get_score() const { return score; }
		void set_score(int s) { score = s;}
		void add_score(int s) { score += s;}
		
		void begin_turn() {
			string tmp;
			cout << "Player " << number << endl;
			do{
				cout << "Enter your pass phrase : ";
				cin >> tmp;
				if(tmp == password) turn = true;
			}while(turn == false);
		}
		void displayscore() { cout << "Your Score : " << score << endl; }
		void displaycards(){
			cout << "Your Hand" << endl;
			Card::print(hand, 3);
			cout << endl;
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

template <class PlayerType = Player>
class GameProvider {
	protected:
		int num_players;
		vector<PlayerType> players;
		vector<cardShort> deck;
		int winner, temp_winner;
	public:
		GameProvider(): winner(0), temp_winner(0),
		players(), deck(),
		num_players(0) {}
		virtual ~GameProvider() {}

		void init_deck() {
			if(deck.empty()){
				deck = vector<cardShort>();
				for(int i = 1; i < 5; i++)
					for(int j = 1; j < 14; j++)
						deck.push_back({ j, i});
			}
			std::random_device rd;
			std::mt19937 g(rd());
			std::shuffle(deck.begin(), deck.end(), g);
		}

		virtual void new_game() {
			init_deck();
			cout << "How many Players ? (max 4)" << endl;
			cin >> num_players;
			num_players = num_players < 0 ? 2 : num_players;
			num_players = num_players > 4 ? 4 : num_players;
			num_players++;										// Plus one for PC
			system("cls");
			
			srand((unsigned int) time(0));
			if(not players.empty()) players.clear();
			for(int i = 0; i < num_players; i++){
				string tmp;
				if(i == 0) tmp = "PC";
				else {
					cout << "Player " << i << " password : ";
					cin >> tmp;
				}
				PlayerType* new_player = new PlayerType(i, tmp, deck.at(3*i), deck.at(3*i + 1), deck.at(3*i + 2));
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
		
		virtual void player_turn(int p_num) {
			PlayerType* player = &players[p_num];
			if(not player->isPlaying()) return;
			player->begin_turn();
			player->displayscore();
			player->displaycards();
			cout<< "What do you want?" << endl
				<< "(C)ontinue" << endl
				<< "(A)bort" << endl;
			char choice;
			cin >> choice;
			switch(choice) {
				case 'C' : case 'c' : {
					player->add_score(rand() % 10);	// Here cin just an example of what we can do
					player->displayscore();
					cout << "Press enter to finish your turn" << endl;
					getchar(); getchar();
 					player->end_turn();
					break;
				}
				case 'A': case 'a': {
					cout << "Do you realy want to give up? (Y)es or anything else to cancel" << endl;
					char tmp;
					cin >> tmp;
					if(tmp == 'Y' or tmp == 'y') {
						player->end_turn();
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
			/* Here cin just an example(that could be overwritten)
			 In the basic situation, the winner of the
			 game cin the one with he highest score
			 Winner equals zero means draw */
			int max_score = -1; // That way, the counter will initialise with player1's score
			for(int i = 1; i < num_players; i++) {
				if(not players[i].isPlaying()) continue;
				if(players[i].get_score() > max_score) { max_score = players[i].get_score(); temp_winner = i; }
				else if(players[i].get_score() == max_score) temp_winner = 0;
			}
			winner = assign ? temp_winner : winner;
		}
		
		virtual bool should_game_continue() {
			/* Here also cin just an example(that should be overwritten)
			 We decide to stop the game when a player the reach a certain score */
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
		
		bool terminate_game() {
			cout << "Game over" << endl;
			for(int i = 1; i < num_players; i++){
				players[i].game_over();
				cout << "Player " << i << " score : " << players[i].get_score()<< endl;
				players[i].displaycards();
				cout << endl;
			}
			if(winner > 0) cout << "Winner : Player " << winner << endl << endl;
			else cout << "Draw" << endl << endl;
			
			char a;
			cout << "Do you want another round? (Y)es or anything else to finish : ";
			cin >> a;
			system("cls");
			if(a == 'Y' or a =='y') return false;
			else return true;
		}
		virtual void game_loop(){
			do {
				new_game();
				do { for(int i = 1; i < num_players; i++) player_turn(i); }
				while(should_game_continue());
				if(terminate_game()) break;
			}while(true);
		}
};

#endif