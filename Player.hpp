#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Card.hpp"
#include "LinkedList.hpp"
#include "DoublyList.hpp"
#include <iostream>
using namespace std;

//class used to represent players within game in main.cpp

class Player {
private:
	//name and hand (containg cards) of the player
    string name;
    LinkedList<Card>* hand;

public:
    //default constructor
    Player();
    //overloaded constructor with name as parameter
	Player(string n);
	//destructor
	virtual ~Player();
	//returns the name of the player
	string getName() const;
	//sorts player's hand by color
	void sortHand();
	//Searches hand for card that can be played given top card of pile, p. returns position & utilizes sequential (binary) search
	int cardSearchCOM(Card p);
	//prints out hand of player
	void printHand();
	//returns the length of Player's hand
	virtual int getLength() const;
	//adds Card to back of hand
	void append(const Card& c);
	//removes card from hand
	void discard(int i);
	//adds card to hand
	Card getCard(int i);
};

#include "Player.tpp"
#endif /* PLAYER_HPP_ */
