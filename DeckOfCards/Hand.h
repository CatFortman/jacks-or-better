//
//     Cat Fortman
//	   May 03 2016
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Card.h"
#include "Deck.h"

#include <vector>
#include <memory>
#include <iostream>
#include <unordered_map>


enum class PokerHand
{
	PAIR,
	TWOPAIR,
	THREEOFAKIND,
	STRAIGHT,
	FLUSH,
	FULLHOUSE,
	FOUROFAKIND,
	STRAIGHTFLUSH,
	ROYALFLUSH	
};

const char* getPokerHandName(PokerHand type)
{
	switch (type)
	{
	case PokerHand::PAIR: return "Pair";
	case PokerHand::TWOPAIR: return "Two Pair";
	case PokerHand::FOUROFAKIND: return "Four of a kind";
	case PokerHand::THREEOFAKIND: return "Three of a kind";
	case PokerHand::FULLHOUSE: return "Full House";
	case PokerHand::STRAIGHT: return "Straight";
	case PokerHand::FLUSH: return "Flush";
	case PokerHand::STRAIGHTFLUSH: return "Straight Flush";
	default : return "Royal Flush";
	}
}


using CardPtr = std::shared_ptr<Card>;

class Hand
{
public:
	Hand(); 
	~Hand();

	void clear(); // clears the hand of cards

	void addCard(CardPtr c); // adds a card to the hand
	void removeCard(int c);  // removes  a card
	void redrawCard(int i, CardPtr c); // redraws a card in your hand

	void initPayoutHands(); // loads the payout map with payouts

	void score(); // checks the hand to see if the player won

	bool isDraw(int idx); // do I draw card at idx
	void toggle(int idx);  //

	int size() const { return _hand.size(); } // returns the size of the hand of cards

	friend std::ostream& operator<<(std::ostream& os, const Hand& h); // overloads the cout operator for hand
	
	bool isPair(); // returns true for a pair of cards
	bool isTwoPair(); // returns true if there is a two pair
	bool isThreeOfAKind(); // returns true for a three of a kind
	bool isFourOfAKind(); // returns true for four of a kind
	bool isFullHouse(); // returns true if you have a full house
	bool isFlush(); // returns true for a flush
	bool isStraight(); // returns true if it is a straight
	bool isStraightFlush(); // checks for a straight flush
	bool isRoyalFlush(); // returns true if it is a royal flush

public:
	std::unordered_map<PokerHand, int> _payoutHands; // map of enums for hand type and win amount

private:
	std::vector<CardPtr> _hand; // holds the cards in a hand vector
	std::vector<bool> _draw; // true if card should draw
};
std::ostream& operator<<(std::ostream& os, const Hand& h);
