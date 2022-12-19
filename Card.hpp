#ifndef CARD_HPP_
#define CARD_HPP_

#include <iostream>
using namespace std;

//Specific class used to represent Cards in the main.cpp program.

class Card {
private:
	//color & value on the card
	string color;
	string value;

public:
	//constructor with color and value as arguments
	Card(string c, string v);
	//default constructor without any arguments
	Card();
	//destructor
	virtual ~Card();
	//returns color of a card
    string getColor() const;
    //returns value of a card
    string getValue() const;
    //Checks if card is valid in comparison to another card
    //first Card represents user's card & second Card represents pile Card, checks if card is valid to be played
    bool validCard(Card c, Card p) const;

};

#include "Card.tpp"
#endif /* CARD_HPP_ */
