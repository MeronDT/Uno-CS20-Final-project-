/*******************************************************************************
 *  Description:
 *      default constructor creates Player
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      creates Player object
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
Player::Player()
:name(), hand(new LinkedList<Card>){ }

/*******************************************************************************
 *  Description:
 *      Constructor with name as parameter, creates Player object
 *
 *  Input(s):
 *      string n, name of the Player
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
Player::Player(string n)
:name(n), hand(new LinkedList<Card>){ }

/*******************************************************************************
 *  Description:
 *      destructor
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
Player::~Player()
{ }

/*******************************************************************************
 *  Description:
 *      returns name of player
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      string, name of player
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
string Player::getName() const{
	return name;
}

/*******************************************************************************
 *  Description:
 *      Sorts hand of Player utilizing selection sort. The colors of the cards
 *      are what get compared and sorted by.
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(N^2)
*******************************************************************************/
void Player::sortHand(){
	int t = -1;
	for(int i = 0; i < hand->getLength() - 1; i++){
        t = i;
        for (int j = hand->getLength() - 1; j > i; j--) {
            if ((hand->getElement(t)).getColor() > (hand->getElement(j)).getColor()) {
                t = j;
            }
        }
        if (i != t) {
        	Card tempCard = hand->getElement(i);
        	hand->replace(i, hand->getElement(t));
        	hand->replace(t, tempCard);
        }
    }
}

/*******************************************************************************
 *  Description:
 *      Searches through hand (most useful with COM players on main.cpp) for a valid card
 *      within the hand, cards are decided on being valid through comparison with given Card
 *
 *  Input(s):
 *      Card p, given Card which the cards in the hand are compared to
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
int Player::cardSearchCOM(Card p){
	for(int i = 0; i < hand->getLength(); i++){
		Card currCard = hand->getElement(i);
		if(currCard.getValue() == "+4"){
			return i;
		}
		else if(currCard.getValue() == "WILD"){
			return i;
		}
		else if(currCard.getColor() == p.getColor()){
			return i;
		}
		else if(currCard.getColor() == "BLACK"){
			return i;
		}
		else if(currCard.getValue() == p.getValue()){
			return i;
		}
	}
	//if a valid card is not found return a negative position to represent failure
	return -1;
}

/*******************************************************************************
 *  Description:
 *      Prints out hand of Player in a way that creates menu for user when running
 *      the main program
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
void Player::printHand(){
	cout << "Player's hand: " << endl;

	for(int i = 0; i < hand->getLength(); i++){
		Card currCard = hand->getElement(i);
		cout << i + 1 << ": " << currCard.getColor() << "-" << currCard.getValue() << endl;
	}

	cout << endl << "Player has: " << hand->getLength() << " cards" << endl;
}

/*******************************************************************************
 *  Description:
 *      returns length of Hand, which is how many cards are in it
 *
 *  Input(s):
 *      NA
 *
 *  Output:
 *      int, length of Hand
 *
 *  Asymptotic Analysis:
 *  O(1)
*******************************************************************************/
int Player::getLength() const{
	return hand->getLength();
}

/*******************************************************************************
 *  Description:
 *      adds given Card to the end of the Hand
 *
 *  Input(s):
 *      const Card& c, given card to be added to end of hand
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
void Player::append(const Card& c){
	hand->append(c);
}

/*******************************************************************************
 *  Description:
 *      removes card at given position from hand
 *
 *  Input(s):
 *      int i, position of card to be removed
 *
 *  Output:
 *      NA
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
void Player::discard(int i){
	hand->remove(i);
}

/*******************************************************************************
 *  Description:
 *      Accesses the card at the given position in hand
 *
 *  Input(s):
 *      int i, position of card to be accessed
 *
 *  Output:
 *      Card, card at position in hand
 *
 *  Asymptotic Analysis:
 *  O(N)
*******************************************************************************/
Card Player::getCard(int i){
	return hand->getElement(i);
}
