/*
  	ICTU - LEVEL 1 - GROUP4
  	Object Oriented Programming - GROUP3
  	Section C
*/

#ifndef __POKER_H__
#define __POKER_H__

#include "player.h"
#include <bits/stdc++.h>

#define GAME_INITIAL_WALLET 1000
#define GAME_INITIAL_CHIP 100
#define GAME_INITIAL_APC (GAME_INITIAL_WALLET / GAME_INITIAL_CHIP)
#define GAME_MIN_BET 10
#define GAME_MAX_BET 50

#define GAME_PHASE_1 1
#define GAME_PHASE_2 2
#define GAME_PHASE_3 3
#define GAME_PHASE_4 4
#define GAME_PHASE_5 5

class PokerPlayer : public Player {
	protected:
		int wallet, in_chips, rem_chips;
		int init_bet;
		bool is_eliminated;
	public:
		PokerPlayer(
			int num, string pass,
			cardShort c1,
			cardShort c2,
			cardShort c3) :
			Player(num, pass, c1, c2, c3),
			wallet(0),
			in_chips(GAME_INITIAL_WALLET / GAME_INITIAL_APC),
			rem_chips(GAME_INITIAL_WALLET / GAME_INITIAL_APC),
			is_eliminated(false), init_bet(GAME_MIN_BET) { if(num == 0) wallet = 20 * GAME_INITIAL_WALLET; }
		virtual ~PokerPlayer() {}
		int get_wallet() const { return wallet; }
		int get_bet() const { return in_chips - rem_chips; }
		int get_rem() const { return rem_chips; }
		bool isEliminated() const { return is_eliminated; }
		void ante(int amount) { init_bet = amount; rem_chips -= amount; } 
		void raise() { rem_chips -= init_bet; }
		void onVictoryCase1(PokerPlayer& dealer) {
			cout<< "The Computer's hand is less than Queen High" << endl
				<< "Therefore, Congrats" << endl;
			rem_chips += 2 * init_bet;
			wallet += init_bet * GAME_INITIAL_APC;
			dealer.wallet -= init_bet * GAME_INITIAL_APC;
			displaywallet();
		}
		void onVictoryCase2(PokerPlayer& dealer) {
			cout<< "The Computer's hand is less than yours" << endl
				<< "Therefore, Congrats" << endl;
			rem_chips += 2 * init_bet;
			wallet += 2 * init_bet * GAME_INITIAL_APC;
			dealer.wallet -= 2 * init_bet * GAME_INITIAL_APC;
			displaywallet();
		}
		void onDraw(PokerPlayer& dealer) {
			cout<< "The Computer's hand is exactly the same as yours" << endl
				<< "Therefore, Draw match" << endl;
			rem_chips += 2 * init_bet;
			displaywallet();
		}
		void onDefeat(PokerPlayer& dealer) {
			cout<< "The Computer's hand is greater than yours" << endl
				<< "Therefore, you lost" << endl;
			displaywallet();
		}
		void displaywallet() { cout << "You have " << wallet << " in wallet" << endl; }
		void displaybet() { cout << "Your bet cin " << in_chips - rem_chips << endl; }
		void eliminate() { is_eliminated = true; is_playing = false; }
		void fold() {
			game_over();
		}
		void new_hand(cardShort c1,cardShort c2, cardShort c3) {
			is_playing = true;
			turn = false;
			delete[] hand;
			hand = new Card[3] { Card(c1), Card(c2), Card(c3) };
		}
		int evaluate_hand() {
			/*
			High Card : 1 - 13
			One pair : 14 - 26
			Flush : 27 - 39
			Straight : 40 - 52
			3 of a Kind : 53 - 65
			Straight Flush : 66 - 78
			*/
			
			vector<Card> sorted = { hand[0], hand[1], hand[2] };
			sort(sorted.begin(), sorted.end(), Card::Less);
			int min_card = sorted[0].get_name();
			int med_card = sorted[1].get_name();
			int max_card = sorted[2].get_name();

			// Straight Flush
			if((hand[0].get_suit() == hand[1].get_suit() and hand[0].get_suit() == hand[2].get_suit())
				and min_card + 1 == med_card and med_card + 1 == max_card) return 65 + max_card ;
			// 3 of a Kind
			else if(hand[0].get_name() == hand[1].get_name() and hand[0].get_name() == hand[2].get_name())
				return 52 + max_card;
			// Straight
			else if(min_card + 1 == med_card and med_card + 1 == max_card)
				return 39 + max_card;
			// Flush
			else if(hand[0].get_suit() == hand[1].get_suit() and hand[0].get_suit() == hand[2].get_suit())
				return 26 + max_card;
			// One Pair
			else if(hand[0].get_name() == hand[1].get_name())
				return 13 + hand[0].get_name();
			else if(hand[0].get_name() == hand[2].get_name())
				return 13 + hand[0].get_name();
			else if(hand[1].get_name() == hand[2].get_name())
				return 13 + hand[1].get_name();
			// High Card
			else return max_card;
		}
};

class PokerProvider : public GameProvider<PokerPlayer> {
	public:
		PokerProvider() {}
		virtual ~PokerProvider() {}
		void new_game() {
			init_deck();
			cout << "How many Players ? (max 4) (There is actually " << num_players << " players)" << endl;
			int new_num_players;
			cin >> new_num_players;
			new_num_players = new_num_players < 0 ? 1 : new_num_players;
			new_num_players = new_num_players > 4 ? 4 : new_num_players;
			new_num_players++;										// Plus one for PC
			
			if(new_num_players == num_players){
				for(int i = 0; i < num_players; i++) {
					if(players[i].isEliminated()) continue;
					if(i != 0) {
						cout<< "Actually, you have " << players[i].get_wallet() << endl
							<< "Do you want to stop there? (Y)es or anything else to continue" << endl;
						char play;
						cin >> play;
						if(play == 'Y' or play == 'y') {
							players[i].eliminate();
							continue;
						}
					}
					players[i].new_hand(deck.at(3*i), deck.at(3*i + 1), deck.at(3*i + 2));
				}
				system("cls");
			}
			else {
				num_players = new_num_players;
				if(not players.empty()) players.clear();
				for(int i = 0; i < num_players; i++){
					string tmp;
					if(i == 0) tmp = "PC";
					else {
						cout << "Player " << i << " password : ";
						cin >> tmp;
					}
					PokerPlayer* new_player = new PokerPlayer(
						i, tmp,
						deck.at(3*i), deck.at(3*i + 1), deck.at(3*i + 2));
					players.push_back(*new_player);
					system("cls");
				}
			}
		}
		void phase1(int p){
			if(players[p].isEliminated()) return;
			PokerPlayer* player = &players[p];
			player->begin_turn();
			cout<< "The Minimal Ante for this table is " << GAME_MIN_BET << endl
				<< "The Maximun Ante for this table is " << GAME_MAX_BET << endl;
			if(player->get_rem() > 2 * GAME_MIN_BET){
				cout<< "How much do you want to bet?" << endl;
				int ante;
				cin >> ante;
				ante = ante < GAME_MIN_BET ? GAME_MIN_BET : ante;
				ante = ante >= (player->get_rem() / 2) ? (player->get_rem() / 2) : ante;
				cout<< "Press Enter to finish this phase" << endl;
			} else {
				player->eliminate();
				cout<< "You cannot afford the coming rounds" << endl
					<< "You are eliminated" << endl
					<< "Press Enter and go aside" << endl;
			}
			getchar();
			player->end_turn();
		}
		void phase2(int p) {
			if(players[p].isEliminated()) return;
			PokerPlayer* player = &players[p];
			player->begin_turn();
			cout << "Player " << p << endl;
			player->displaycards();
			cout 	<< "What do you want?" << endl
				<< "(R)aise" << endl
				<< "(F)old" << endl;
			char choice;
			cin >> choice;
			switch (choice) {
				case 'R': case 'r': {
					player->raise();
					player->set_score(player->evaluate_hand());
					cout << "Press enter to finish your turn" << endl;
					getchar(); getchar();
 					player->end_turn();
					break;
				}
				case 'F': case 'f': {
					player->fold();
					cout << "Press enter to finish your turn" << endl;
					getchar(); getchar();
 					player->end_turn();
					break;
				}
				default: {
					player->end_turn();
					break;
				}
			}
		}
		void phase3(int p) {
			if(players[p].isEliminated()) return;
			PokerPlayer* player = &players[p];
			PokerPlayer* dealer = &players[0];
			cout << "Player " << p << " vs Dealer" << endl << endl;
			cout << "(Dealer)" << endl;
			dealer->displaycards();
			cout << "(Player "<< p <<")";
			player->displaycards();
			int diff = player->get_score() - dealer->get_score();
			if(dealer->get_score() < CARD_NAME_QUEEN) player->onVictoryCase1(*dealer);
			else if(diff > 0) player->onVictoryCase2(*dealer);
			else if(diff == 0) player->onDraw(*dealer);
			else player->onDefeat(*dealer);
			cout << "Press Enter to continue";
			getchar();
		}
		int evaluate_winner(int player) {
			if(players[0].get_score() == players[player].get_score()) return -1;
			else return players[0].get_score() > players[player].get_score() ? 0 : player;
		}
		bool should_game_continue() { return (players[0].get_wallet() > 5 * GAME_INITIAL_WALLET); }
		void game_loop() {
			do{
				new_game();
				PokerPlayer* dealer = &players[0];
				for (int i = 1; i < num_players; i++) phase1(i);
				bool isplayers = true;
				for(int i = 1; i < num_players; i++)
					if(players[i].isEliminated()) isplayers = false;
				if(not isplayers) break;
				for (int i = 1; i < num_players; i++) phase2(i);
				dealer->set_score(dealer->evaluate_hand());
				for (int i = 1; i < num_players; i++) phase3(i);

				if(not should_game_continue()) {
					cout<< "The Computer cannot afford another round" << endl
						<< "(Press enter to terminate)";
					getchar(); getchar();
					break;
				}
				char a;
				cout << "Do you want another round? (Y)es or anything else to finish : ";
				cin >> a;
				system("cls");
				if(not (a == 'Y' or a =='y')) break;
			}while(true);
		}
};

#endif