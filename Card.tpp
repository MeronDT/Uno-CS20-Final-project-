/*******************************************************************************
 *  Description:
 *      creates a Card object with specified color and value
 *
 *  Input(s):
 *      string c, the desired color for the card that will be made
 *      string v, the desired value for the card that will be made
 *
 *  Output:
 *      creates new Card object
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
Card::Card(string c, string v)
: color(c), value(v) { }

/*******************************************************************************
 *  Description:
 *      creates a Card object
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      creates new Card object
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
Card::Card()
: color(""), value("") { }

/*******************************************************************************
 *  Description:
 *      Destructor clears memory on the Card objects
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      creates new Card object
 *
 *  Asymptotic Analysis:
 *  O(0)
*******************************************************************************/
Card::~Card()
{}

/*******************************************************************************
 *  Description:
 *      gives the color of a Card
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      string, the color of a card (BLACK, RED, YELLOW, BLUE, or GREEN)
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
string Card::getColor() const{
	return color;
}

/*******************************************************************************
 *  Description:
 *      gives the value of a Card
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      string, the value of a card (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, REVERSE, SKIP, +2, +4, WILD)
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
string Card::getValue() const{
	return value;
}

/*******************************************************************************
 *  Description:
 *      Checks to see if a Card is valid when being comapred to another card. This is done
 *      by looking at the color and values of the two cards. If a card matches the color or value,
 *      or card is BLACK color it will be valid. Within main.cpp used to check if a player can
 *      put a card on the Card pile or not. Card of player is trying to match the card on the pile.
 *
 *  Input(s):
 *      Card c, Card of the player
 *      Card p, Card on the top of the pile.
 *
 *  Output:
 *      string, the color of a card (BLACK, RED, YELLOW, BLUE, or GREEN)
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
bool Card::validCard(Card c, Card p) const{
	//if color or value matches, or card is black then valid to be played
	if(c.color == p.color){
		return true;
	}
	else if(c.color == "Black"){
		return true;
	}
	else if(c.value == p.value){
		return true;
	}
	else{
		return false;
	}
}
