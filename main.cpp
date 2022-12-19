#include <iostream>
#include <ctime>
#include <vector>
#include "ArrayStack.hpp"
#include "Player.hpp"
#include "LinkedList.hpp"
#include "DoublyList.hpp"
#include "Deque.hpp"
using namespace std;

int main(){

	int userChoice = 0;
	//Display Main Menu
	do{
	cout << endl << "Welcome to UNO " << endl << "Enter the number of of your choice " << endl << endl;
	cout << "1: Play" << endl
		 << "2: How to Play" << endl
		 << "3: Credits" << endl
		 << "4: Exit" << endl;
	cin >> userChoice;

	if(userChoice == 1){
		//ask user how many COM they want to play with
		int numCOM = 0;
		do{
			cout << "How many COM players would you like? (enter an integer 1-3):";
			cin >> numCOM;
		}
		while(numCOM <= 0 || numCOM > 3);
		//Creates deck of cards, size of 108 for standard Uno deck
		const int DECK_SIZE = 108;
		//Vector to represent a fresh deck Right out the box;
    	vector<Card> freshDeck;

	    // seed RNG
	    srand(time(0));

	    //create two arrays which hold the different possible colors and values of cards
	    const int COLOR_SIZE = 5;
	    const int VALUE_SIZE = 15;
	    string color[COLOR_SIZE] = {"RED","BLUE","GREEN","YELLOW","BLACK"};
	    string value[VALUE_SIZE] = {"0","1","2","3","4","5","6","7","8","9","REVERSE","SKIP","+2","+4","WILD"};

	    //single 0 of each color
	    for(int i = 0; i < COLOR_SIZE - 1; i++){
	    	freshDeck.push_back(Card(color[i], "0"));
	    }

	    //double of rest, not including black cards
	    for(int i = 0; i < COLOR_SIZE - 1; i++) {
	        for (int j = 1; j < VALUE_SIZE - 2; j++) {
	        	freshDeck.push_back(Card(color[i], value[j]));
	        	freshDeck.push_back(Card(color[i], value[j]));
	        }
	    }
	    //four of black cards
	    for(int i = 13; i < VALUE_SIZE; i++){
			freshDeck.push_back(Card("BLACK", value[i]));
			freshDeck.push_back(Card("BLACK", value[i]));
			freshDeck.push_back(Card("BLACK", value[i]));
			freshDeck.push_back(Card("BLACK", value[i]));
	    }

	    //Deck that will be played with
		Deque<Card> gameDeck;

		//array to represent positions of Fresh deck vector to prevent same card from being enqueued > once
		bool positions[DECK_SIZE];
		for(int i = 0; i < DECK_SIZE; i++){
			positions[i] = false;
		}

		//randomizing positions of cards, the shuffling of the deck
	    do{
	    	int x = rand() % (DECK_SIZE);
	    	if(positions[x] == false){
	    		gameDeck.enqueueBack(freshDeck[x]);
	    		positions[x] = true;
	    	}
	    }
	    while(gameDeck.getLength() != DECK_SIZE);

		//Creates pile where cards will be played to, max size of 1000 since more than 1 full deck can be used
		ArrayStack<Card> gamePile(1000);

		//move top card of gameDeck to gamePile & redo until starting card is not black
		do{
			gamePile.push(gameDeck.front());
			gameDeck.dequeueFront();
		}
		while(gamePile.peek().getColor() == "BLACK");

	    //create linked list of players to represent turn order giving each player 5 cards
	    DoublyList<Player> playerList;
	    Player userPlayer = Player("USER");
	    for(int k = 0; k < 5; k++){
	    	userPlayer.append(gameDeck.front());
	    	gameDeck.dequeueFront();
	    }

	    playerList.append(userPlayer);
	    if(numCOM == 1 || numCOM == 2 || numCOM == 3){
	    	Player COM1Player = Player("COM1");
		    for(int k = 0; k < 5; k++){
		    	COM1Player.append(gameDeck.front());
		    	gameDeck.dequeueFront();
		    }

		    playerList.append(COM1Player);
	    }
	    if(numCOM == 2 || numCOM == 3){
	    	Player COM2Player = Player("COM2");
		    for(int k = 0; k < 5; k++){
		    	COM2Player.append(gameDeck.front());
		    	gameDeck.dequeueFront();
		    }

		    playerList.append(COM2Player);
	    }
	    if(numCOM == 3){
	    	Player COM3Player = Player("COM3");
		    for(int k = 0; k < 5; k++){
		    	COM3Player.append(gameDeck.front());
		    	gameDeck.dequeueFront();
		    }

		    playerList.append(COM3Player);
	    }

	    //check which player turn it is after user/COM turn move linked list forward to next turn
	    //winner string will be used to check for winner & know which player won
	    string winner = "";
	    int playerListPosition = 0;
	    //variable to represent direction of turns since reverse card can change it
	    bool forwardOrder = true;
	    bool takeTwo = false;
	    bool takeFour = false;

		//look at top card of pile and print it out
		Card topPile = gamePile.peek();
		cout << "The first card on the pile is: " << topPile.getColor() << "-" << topPile.getValue() << endl << endl;

	    do{

	    	//Playerlist current position calculated by absolute value of PlayerListPosition % length
	    	Player turnPlayer = playerList.getElement(abs(playerListPosition % playerList.getLength()));

	    	if(turnPlayer.getName() == "USER"){
	    		int userCardChoice = 0;

	    		do{
	    			//print current top card of pile, print user's hand, and list options for user
	    			cout << "The top card on the pile is " << gamePile.peek().getColor() << "-" << gamePile.peek().getValue() << endl << endl;

	    			//if previous person has used effect
	    			if(takeTwo == true){
	    				takeTwo = false;
	    				cout << "You must draw two cards" << endl;
   					 int topBot = 0;
   					 do{
   						 cout << "Would you like to draw from the top (enter 1) or bottom (enter 2) of the deck" << endl;
   						 cin >> topBot;
   					 }
   					 while(topBot != 1 && topBot != 2);
   					 if(topBot == 1){
   						 //move top card of deck to user's hand
   						 turnPlayer.append(gameDeck.front());
   						 gameDeck.dequeueFront();
   						 turnPlayer.append(gameDeck.front());
   						 gameDeck.dequeueFront();
   					 }
   					 else{
   						 //move bottom card of deck to user's hand
   						 turnPlayer.append(gameDeck.back());
   						 gameDeck.dequeueBack();
   						 turnPlayer.append(gameDeck.front());
   						 gameDeck.dequeueFront();
   					 }
	    			}
	    			else if(takeFour == true){
	    				takeFour = false;
	    				cout << "You must draw four cards" << endl;
   					 int topBot = 0;
   					 do{
   						 cout << "Would you like to draw from the top (enter 1) or bottom (enter 2) of the deck" << endl;
   						 cin >> topBot;
   					 }
   					 while(topBot != 1 && topBot != 2);
   					 if(topBot == 1){
   						 //move top card of deck to User's hand
   						 turnPlayer.append(gameDeck.front());
   						 gameDeck.dequeueFront();
   						 turnPlayer.append(gameDeck.front());
   						 gameDeck.dequeueFront();
   						 turnPlayer.append(gameDeck.front());
   						 gameDeck.dequeueFront();
   						 turnPlayer.append(gameDeck.front());
   						 gameDeck.dequeueFront();
   					 }
   					 else{
   						 //move bottom card of deck to user's hand
   						 turnPlayer.append(gameDeck.back());
   						 gameDeck.dequeueBack();
   						 turnPlayer.append(gameDeck.front());
   						 gameDeck.dequeueFront();
   						 turnPlayer.append(gameDeck.back());
   						 gameDeck.dequeueBack();
   						 turnPlayer.append(gameDeck.front());
   						 gameDeck.dequeueFront();
   					 }
	    			}

		    		turnPlayer.printHand();
	    			cout << "Select a move by entering the option's number" << endl
	    				 << "1: Play a card" << endl
						 << "2: Draw a card" << endl
						 << "3: Sort your hand" << endl
						 << "4: forfeit" << endl;
	    			 cin >> userChoice;

	    			 if(userChoice == 1){
	    				 //Check if user can play a valid card or not
	    				 int testInt = turnPlayer.cardSearchCOM(gamePile.peek());
	    				 //if user cannot play a valid card, they are forced to draw one
	    				 if(testInt == -1){
	    					 //check if deck is empty and refill if it is
	    					 if(gameDeck.isEmpty()){
	    						 //array to represent positions of Fresh deck vector to prevent same card from being enqueued > once
	    						 bool positions[DECK_SIZE];
	    						 for(int i = 0; i < DECK_SIZE; i++){
	    							 positions[i] = false;
	    						 }

	    						 //randomizing positions of cards, the shuffling of the deck
	    						 do{
	    							 int x = rand() % (DECK_SIZE);
	    							 if(positions[x] == false){
	    								 gameDeck.enqueueBack(freshDeck[x]);
	    								 positions[x] = true;
	    							 }
	    						 }
	    						 while(gameDeck.getLength() != DECK_SIZE);
	    					 }

	    					 int topBot = 0;
	    					 do{
	    						 cout << "Would you like to draw from the top (enter 1) or bottom (enter 2) of the deck" << endl;
	    						 cin >> topBot;
	    					 }
	    					 while(topBot != 1 && topBot != 2);
	    					 if(topBot == 1){
	    						 //move top card of deck to COM's hand
	    						 turnPlayer.append(gameDeck.front());
	    						 gameDeck.dequeueFront();
	    					 }
	    					 else{
	    						 //move bottom card of deck to COM's hand
	    						 turnPlayer.append(gameDeck.back());
	    						 gameDeck.dequeueBack();
	    					 }
	    				 }
	    				 else{
	    					 do{
	    						 cout << "Enter the card number you would like to play:" << endl;
	    						 cin >> userCardChoice;
	    					 }
	    					 while(userCardChoice < 1 || userCardChoice > turnPlayer.getLength());
	    				 }

	    				 //test if player's card is valid, if valid play it, if not ask for new card
	    				bool validPlay = false;
	    				do{
	    				 Card attemptCard = turnPlayer.getCard(userCardChoice - 1);
	    					 //if card is valid
	    					 if(attemptCard.getColor() == "BLACK" || attemptCard.getColor() == gamePile.peek().getColor() ||
	    						attemptCard.getValue() == gamePile.peek().getValue()){
	    						 //Move card from hand to top of pile
	    						 gamePile.push(attemptCard);
	    						 turnPlayer.discard(userCardChoice - 1);

	    						 //Apply any effects
	    						 if(gamePile.peek().getValue() == "REVERSE"){
	    							 forwardOrder = !forwardOrder;
	    						 }
	    						 else if(gamePile.peek().getValue() == "SKIP"){
	    							 if(forwardOrder == true){
	    								 playerListPosition++;
	    							 }
	    							 else{
	    								 playerListPosition--;
	    							 }
	    						 }
	    						 else if(gamePile.peek().getValue() == "+2"){
	    							 takeTwo = true;
	    						 }
	    						 else if(gamePile.peek().getValue() == "+4"){
	    							 takeFour = true;

	    							 string userChoseColor = "";
	    							 do{
	    								 cout << "Chose a color for the top of the pile (RED, BLUE, GREEN, or YELLOW)" << endl;
	    								 cin >> userChoseColor;
	    							 }
	    							 while(userChoseColor != "RED" && userChoseColor != "BLUE" &&
	    									 userChoseColor != "YELLOW" && userChoseColor != "GREEN");

	    							 //add wild of chosen color to top of pile
	    							 gamePile.push(Card(userChoseColor, "+4"));
	    						 }
	    						 else if(gamePile.peek().getValue() == "WILD"){
	    							 string userChoseColor = "";
	    							 do{
	    								 cout << "Chose a color for the top of the pile (RED, BLUE, GREEN, or YELLOW)" << endl;
	    								 cin >> userChoseColor;
	    							 }
	    							 while(userChoseColor != "RED" && userChoseColor != "BLUE" &&
	    								   userChoseColor != "YELLOW" && userChoseColor != "GREEN");

	    							 //add wild of chosen color to top of pile
	    							 gamePile.push(Card(userChoseColor, "WILD"));
	    						 }

	    						 //toggle to exit loop
	    						 validPlay = true;
	    					 }
	    					 else{
	    						 do{
	    							 cout << "Enter the card number you would like to play:" << endl;
	    							 cin >> userCardChoice;
	    						 }
	    						 while(userCardChoice < 1 || userCardChoice > turnPlayer.getLength());
	    					 }
	    				}
	    				while(validPlay == false);
	    			 }
	    			 else if(userChoice == 2){
	    				 //check if deck is empty and refill if it is
	    				 if(gameDeck.isEmpty()){
	    					 //array to represent positions of Fresh deck vector to prevent same card from being enqueued > once
	    					 bool positions[DECK_SIZE];
	    					 for(int i = 0; i < DECK_SIZE; i++){
	    						 positions[i] = false;
	    					 }

	    					 //randomizing positions of cards, the shuffling of the deck
	    					 do{
	    						 int x = rand() % (DECK_SIZE);
	    						 if(positions[x] == false){
	    							 gameDeck.enqueueBack(freshDeck[x]);
	    							 positions[x] = true;
	    						 }
	    					 }
	    					 while(gameDeck.getLength() != DECK_SIZE);
	    				}

	    				int topBot = 0;
	    				do{
	    					cout << "Would you like to draw from the top (enter 1) or bottom (enter 2) of the deck" << endl;
	    					cin >> topBot;
	    				}
	    				while(topBot != 1 && topBot != 2);
	    				if(topBot == 1){
	    					//move top card of deck to COM's hand
	    					turnPlayer.append(gameDeck.front());
	    					gameDeck.dequeueFront();
	    				}
	    				else{
	    					//move bottom card of deck to COM's hand
	    					turnPlayer.append(gameDeck.back());
	    					gameDeck.dequeueBack();
	    				}

	    			 }
	    			 else if(userChoice == 3){
	    				 turnPlayer.sortHand();
	    			 }
	    			 else if(userChoice == 4){
	    				 winner = "FORFEIT";
	    			 }
	    			 else{
	    				cout << "Invalid option selected" << endl;
	    			 }

	    		}
	    		while(userChoice != 1 && userChoice != 2 && userChoice != 4);

	    		//check if player has 1 or 0 cards
	    		if(turnPlayer.getLength() == 1){
	    			cout << turnPlayer.getName() << " :UNO!" << endl;
	    		}
	    		else if(turnPlayer.getLength() == 0){
	    			winner = turnPlayer.getName();
	    		}

	    		//moving to next player
	    		if(forwardOrder == true){
	    			playerListPosition++;
	    		}
	    		else{
	    			playerListPosition--;
	    		}

	    	}
	    	//COM turn
	    	else{
	    		if(takeTwo == true){
	    			takeTwo = false;
	    			turnPlayer.append(gameDeck.front());
	    			gameDeck.dequeueFront();
	    			turnPlayer.append(gameDeck.front());
	    			gameDeck.dequeueFront();
	    		}
	    		else if(takeFour == true){
	    			takeFour = false;
	    			turnPlayer.append(gameDeck.front());
	    			gameDeck.dequeueFront();
	    			turnPlayer.append(gameDeck.front());
	    			gameDeck.dequeueFront();
	    			turnPlayer.append(gameDeck.front());
	    			gameDeck.dequeueFront();
	    			turnPlayer.append(gameDeck.front());
	    			gameDeck.dequeueFront();
	    		}

	    		//check if COM can play a valid card
	    		int testInt = turnPlayer.cardSearchCOM(gamePile.peek());
	    		if(testInt != -1){
	    			//use the card at the position for their turn
					 //Move card from hand to top of pile
					 gamePile.push(turnPlayer.getCard(testInt));
					 turnPlayer.discard(testInt);
					 cout << turnPlayer.getName() << " Played: " << gamePile.peek().getColor() << "-" << gamePile.peek().getValue() << endl;

					 //Apply any effects
					 if(gamePile.peek().getValue() == "REVERSE"){
						 forwardOrder = !forwardOrder;
					 }
					 else if(gamePile.peek().getValue() == "SKIP"){
						 if(forwardOrder == true){
							 playerListPosition++;
						 }
						 else{
							 playerListPosition--;
						 }
					 }
					 else if(gamePile.peek().getValue() == "+2"){
						 takeTwo = true;
					 }
					 else if(gamePile.peek().getValue() == "+4"){
						 takeFour = true;

						 string COMChoseColor = "";
						 COMChoseColor = "YELLOW";

						 //add wild of chosen color to top of pile
						 gamePile.push(Card(COMChoseColor, "+4"));
					 }
					 else if(gamePile.peek().getValue() == "WILD"){
						 string COMChoseColor = "";
						 COMChoseColor = "RED";

						 //add wild of chosen color to top of pile
						 gamePile.push(Card(COMChoseColor, "WILD"));

					 }
	    		}
	    		else{
    				//move top card of deck to COM's hand
    				turnPlayer.append(gameDeck.front());
    				gameDeck.dequeueFront();
	    		}

	    		//check if player has 1 or 0 cards
	    		if(turnPlayer.getLength() == 1){
	    			cout << turnPlayer.getName() << " :UNO!" << endl;
	    		}
	    		else if(turnPlayer.getLength() == 0){
	    			winner = turnPlayer.getName();
	    		}

	    		//moving to next player
	    		if(forwardOrder == true){
	    			playerListPosition++;
	    		}
	    		else{
	    			playerListPosition--;
	    		}

	    	}

	    	//After each turn check if deck has become empty & if empty redo shuffling of new deck from before
	    	if(gameDeck.isEmpty()){
	    		//array to represent positions of Fresh deck vector to prevent same card from being enqueued > once
	    		bool positions[DECK_SIZE];
	    		for(int i = 0; i < DECK_SIZE; i++){
	    			positions[i] = false;
	    		}

	    		//randomizing positions of cards, the shuffling of the deck
	    	    do{
	    	    	int x = rand() % (DECK_SIZE);
	    	    	if(positions[x] == false){
	    	    		gameDeck.enqueueBack(freshDeck[x]);
	    	    		positions[x] = true;
	    	    	}
	    	    }
	    	    while(gameDeck.getLength() != DECK_SIZE);
	    	}

	    }
	    while(winner == "");

	    if(winner == "FORFEIT"){
	    	cout << "Wow, you really gave up that quickly?? Better luck next time." << endl;
	    }
	    else if(winner == "USER"){
	    	cout << "CONGRATULATIONS, you just won!!" << endl;
	    }
	    else{
	    	cout << "Darn, you were so close to winning but " << winner << " had different plans" << endl;
	    }

	}
	else if(userChoice == 2){
		cout << "Uno is a card game where each player's goal is to get rid of their cards before all their opponents." << endl
			 << "Each player starts with the same number of cards, "
			 << "and at the start of the game a card is taken from the deck and placed on top of the pile." << endl
			 << "The players then each take turns either putting a card from their hand onto the pile or drawing from the deck." << endl
			 << "Not all cards can be played at any time, to play a card it must either have the same color or value as the one atop the deck." << endl
			 << "There is exception to this rule, black wild or +4 cards can be played at any time and allow the player to pick what color they should be treated as." << endl
			 << "The deck consists of Red, Blue, Yellow, Green, and Black cards." << endl
			 << "Card values range from 0-9, as well as +2, +4, wild, reverse, and skip." << endl
			 << "Cards with values 0-9 do not have any extra effects." << endl
			 << "+2 cards will force the next player to draw 2 cards and have their turn skipped." << endl
			 << "+4 cards will force the next player to draw 4 cards and have their turned skipped, it also lets the player pick what color the card should be treated as." << endl
			 << "Wild cards lets the player pick what color the card should be treated as," << endl
			 << "Reverse cards will reverse the player turn order," << endl
			 << "Skip will skip the next player's turn." << endl
			 << "For more information on the game visit the official website at 'https://www.letsplayuno.com/'" << endl << endl;
	}
	else if(userChoice == 3){
		cout << "Uno orginiated in the city of Reading, Ohio. " << endl
			 << "It was created by Merle Robbins in 1971 with his family." << endl
			 << "This Uno project originated in the city of Livermore, California." << endl
			 << "It was created by Meron Tesfandrias in 2022 for a college cs course" << endl << endl;
	}
	else if(userChoice == 4){
		cout << "Thank you for playing!!!" << endl;
	}
	else{
		cout << "Invalid option selected" << endl;
		userChoice = 0;
	}

	}
	while(userChoice != 4);

	//terminate
	return 0;
}
