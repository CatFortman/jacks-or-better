//
//     Cat Fortman
//	   May 03 2016
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <ctime>
#include "Card.h"
#include "VideoPoker.h"
#include "Deck.h"
#include "Hand.h"

int main(int argc, char *argv[])
{

	srand(static_cast<unsigned int>(time(0)));

	
	
	/*Deck deck; // creates deck of cards

	deck.shuffle();  // shuffles the deck

	Hand hand;  // instantiates a hand of cards

	hand.addCard(deck.draw());

	std::cout << hand;  // show cards

	/*if (hand.isRoyalFlush())
	{
		std::cout << "You have a ROYAL FLUSH!!!" << std::endl;
	}
	

	hand.clear(); */
	VideoPoker game;

	game.play();

	system("pause");
	}

