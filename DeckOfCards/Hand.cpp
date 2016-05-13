//
//     Cat Fortman
//	   May 03 2016
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Hand.h"
#include "Deck.h"
#include "Card.h"
#include <map>
#include <algorithm>

Hand::Hand() // initializes the payouts
{
	initPayoutHands();
}


Hand::~Hand()
{
}

void Hand::clear() // clears all the cards in hand
{
	_hand.clear();
}

void Hand::addCard(CardPtr c) // adds a card to hand
{
	_hand.push_back(c);
	_draw.push_back(false);
}

void Hand::removeCard(int c) // remoces a card from the hand
{
	_hand.erase(_hand.begin() + (c - 1));
}

void Hand::redrawCard(int i, CardPtr c)
{
	_hand[i - 1] = c; //draws a new card from the deck and places it in the position the player picked
}

void Hand::initPayoutHands() // loads the payout mao with enum and bools
{
	std::pair<PokerHand, bool> pair(PokerHand::PAIR, false);
	std::pair<PokerHand, bool> twoPair(PokerHand::TWOPAIR, false);
	std::pair<PokerHand, bool> threeOfAKind(PokerHand::THREEOFAKIND, false);
	std::pair<PokerHand, bool> straight(PokerHand::STRAIGHT, false);
	std::pair<PokerHand, bool> flush(PokerHand::FLUSH, false);
	std::pair<PokerHand, bool> fullHouse(PokerHand::FULLHOUSE, false);
	std::pair<PokerHand, bool> fourOfAKind(PokerHand::FOUROFAKIND, false);
	std::pair<PokerHand, bool> straightFlush(PokerHand::STRAIGHTFLUSH, false);
	std::pair<PokerHand, bool> royalFlush(PokerHand::ROYALFLUSH, false);

	_payoutHands.insert(pair);
	_payoutHands.insert(twoPair);
	_payoutHands.insert(threeOfAKind);
	_payoutHands.insert(straight);
	_payoutHands.insert(flush);
	_payoutHands.insert(fullHouse);
	_payoutHands.insert(fourOfAKind);
	_payoutHands.insert(straightFlush);
	_payoutHands.insert(royalFlush);
}


void Hand::score()  //checks the hand for a win
{

	if (isRoyalFlush())
		_payoutHands[PokerHand::ROYALFLUSH] = true;
	else if (isStraightFlush())
		_payoutHands[PokerHand::STRAIGHTFLUSH] = true;
	else if (isFourOfAKind())
		_payoutHands[PokerHand::FOUROFAKIND] = true;
	else if (isFullHouse())
		_payoutHands[PokerHand::FULLHOUSE] = true;
	else if (isFlush())
		_payoutHands[PokerHand::FLUSH] = true;
	else if (isStraight())
		_payoutHands[PokerHand::STRAIGHT] = true;
	else if (isThreeOfAKind())
		_payoutHands[PokerHand::THREEOFAKIND] = true;
	else if (isTwoPair())
		_payoutHands[PokerHand::TWOPAIR] = true;
	else if (isPair())
		_payoutHands[PokerHand::PAIR] = true;
}

bool Hand::isDraw(int idx) // checks if you want to draw a card
{
	if (_draw[idx] == true)  
		return true;
	else
		return false;
}

void Hand::toggle(int idx)
{
	_draw[idx - 1] = !_draw[idx - 1]; // allows player to toggle between draw and hold
}

std::ostream& operator<<(std::ostream& os, const Hand& h)  // overloads the cout operator 
{
	int i = 1;
	int j = 0;
	while (j < h.size()) {
		if (h._draw[j] == true)
			std::cout << i << ") " << *h._hand[j] << " (draw)" << std::endl;
		else
			std::cout << i << ") " << *h._hand[j] << " (hold)" << std::endl;

		i++;
		j++;

	}

	return os;
}


bool Hand::isPair()					// returns boolean if there is a pair and number
{
	bool isPair = false;
	
	/*auto pairLambda = [](std::pair<Face, int> e) {
		(e.second == 2);
	};*/

	std::map<Face, int> h;


		for (int i = 0; i < _hand.size(); i++)
		{
			if(_hand[i]->face == Face::KING || _hand[i]->face == Face::QUEEN || _hand[i]->face == Face::JACK || _hand[i]->face == Face::ACE)
			h[_hand[i]->face]++;
		}

		int pairCount = count_if(h.begin(), h.end(), [](std::pair<Face, int> e) {return (e.second == 2); });
		if (pairCount == 1)
		{
			isPair = true;
		}

		return isPair;

}

bool Hand::isTwoPair()					// returns boolean if there is a pair and number
{
	bool isTwoPair = false;

	/*auto pairLambda = [](std::pair<Face, int> e) {
	(e.second == 2);
	};*/

	std::map<Face, int> h;


	for (int i = 0; i < _hand.size(); i++)
	{
		h[_hand[i]->face]++;
	}

	int pairCount = count_if(h.begin(), h.end(), [](std::pair<Face, int> e) {return (e.second == 2); }); // checks if there are two
	if (pairCount > 1)
	{
		isTwoPair = true;
	}

	return isTwoPair;

}

bool Hand::isThreeOfAKind()					// returns boolean if there is a pair and number
{
	bool isThree = false;

	/*auto pairLambda = [](std::pair<Face, int> e) {
	(e.second == 2);
	};*/

	std::map<Face, int> h;

		for (int i = 0; i < _hand.size(); i++)
		{
			h[_hand[i]->face]++;
		}

		int threeCount = count_if(h.begin(), h.end(), [](std::pair<Face, int> e) {return (e.second == 3); });
		if (threeCount > 0)
		{
			isThree = true;
		}

		return isThree;

}

bool Hand::isFourOfAKind()					// returns boolean if there is a 4 of a kind
{
	bool isFour = false;

	/*auto pairLambda = [](std::pair<Face, int> e) {
	(e.second == 2);
	};*/

	std::map<Face, int> h;


	
		for (int i = 0; i < _hand.size(); i++)
		{
			h[_hand[i]->face]++;
		}

		int fourCount = count_if(h.begin(), h.end(), [](std::pair<Face, int> e) {return (e.second == 4); }); // checks if there are four
		if (fourCount > 0)
		{
			isFour = true;
		}

		return isFour;
}



bool Hand::isFullHouse()					// returns boolean if there is a fullhouse
{
	return(isPair() && isThreeOfAKind());	
}

bool Hand::isFlush()					// returns boolean if there is a flush
{
	bool isFlush = false;

	/*auto pairLambda = [](std::pair<Face, int> e) {
	(e.second == 2);
	};*/

	std::set<Suit> h;



	for (int i = 0; i < _hand.size(); i++)
	{
		h.insert(_hand[i]->suit);
	}


	if (h.size() == 1)
	{
		isFlush = true;
	}

	return isFlush;
}

bool Hand::isStraight()					// returns boolean if there is a flush
{
	bool isStraight = false;

	/*auto pairLambda = [](std::pair<Face, int> e) {
	(e.second == 2);
	};*/

	std::set<int> h;                           // set holds hand values
	

	for (int i = 0; i < _hand.size(); i++)     // inserts the face values as ints in the set
	{
		h.insert((int)_hand[i]->face);
	}

	auto first = h.begin();					   // starts the beginning of the set	
	auto last = h.end();					   // states the end of the set

	last--;									   // gets the last value of the set

	if (h.size() == 5)						   // if the hand size is 5
	{
		if (*first == (*last - 4))			   // if the end subtracted by the beginning equals the first card
		{
			isStraight = true;				   // set as true
		}
	}

	if (*first == 0)						   // if the first card is an ace take in account an ace as a higher value
	{
		h.insert(13);						   // insert phony ace
	}

	last++;

	if (h.size() == 6)						   // test new hand size
	{
		*first++;
		if (*first == (*last - 4))
		{
			isStraight = true;
		}
	}

	return isStraight;
}

bool Hand::isStraightFlush()
{
	return(isStraight() && isFlush());
}

bool Hand::isRoyalFlush() // checks if there is a royal flush
{
	bool isRF = false;

	std::set<int> h;

	if (isStraightFlush())
	{
		for (int i = 0; i < _hand.size(); i++)     // inserts the face values as ints in the set
		{
			h.insert((int)_hand[i]->face);
		}
	}

	auto start = h.begin();

	if (h.size() == 5)
	{
		if (*start == 0)
		{
			h.insert(13);
		}

		auto last = h.end();
		last--;

		if (*last == 13)
		{
			last--;
			if (*last == 12)
			{
				isRF = true;
			}
		}
	}
	

 	return isRF;
}











