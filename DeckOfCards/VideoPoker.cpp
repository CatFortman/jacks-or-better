//
//     Cat Fortman
//	   May 03 2016
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "VideoPoker.h"

VideoPoker::VideoPoker()
{
	initPayouts();
}

VideoPoker::~VideoPoker()
{
}

void VideoPoker::play() //plays the game until the player quits
{

	int choice;
	bool leave = false;
	while (leave != true)
	{
		welcome();

		playOptions();

		std::cout << "\nPlayer credits: " << credits << "\n";

		std::cin >> choice;

		while (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
			std::cin >> choice;
		}
		std::cin.ignore();
		switch (choice) {
		case 1:
			payTable();
			break;
		case 2:
			game();
			break;

		case 3:
			leave = true;
			break;
		default:
			break;
		};
		system("cls");
	}
	system("cls");
}

void playOptions()
{

}

void VideoPoker::payTable() const //shows the payout table
{

	system("cls");
	std::cout << "\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n" <<
		"\txx                                       xx\n" <<
		"\txx   Hand              -      Credits    xx\n" <<
		"\txx_______________________________________xx\n" <<
		"\txx                                       xx\n" <<
		"\txx   Royal Flush       -       250       xx\n" <<
		"\txx_______________________________________xx\n" <<
		"\txx                                       xx\n" <<
		"\txx   Straight flush    -        50       xx\n" <<
		"\txx_______________________________________xx\n" <<
		"\txx                                       xx\n" <<
		"\txx   Four of a kind    -         25      xx\n" <<
		"\txx_______________________________________xx\n" <<
		"\txx                                       xx\n" <<
		"\txx   Full House        -          9      xx\n" <<
		"\txx_______________________________________xx\n" <<
		"\txx                                       xx\n" <<
		"\txx   Flush             -          6      xx\n" <<
		"\txx_______________________________________xx\n" <<
		"\txx                                       xx\n" <<
		"\txx   Straight          -          4      xx\n" <<
		"\txx_______________________________________xx\n" <<
		"\txx                                       xx\n" <<
		"\txx   Three of a kind   -          3      xx\n" <<
		"\txx_______________________________________xx\n" <<
		"\txx                                       xx\n" <<
		"\txx   Two pair          -          2      xx\n" <<
		"\txx_______________________________________xx\n" <<
		"\txx                                       xx\n" <<
		"\txx   Jacks of better   -          1      xx\n" <<
		"\txx_______________________________________xx\n" <<
		"\txx                                       xx\n" <<
		"\txx   Theoretical Return-         98.4%   xx\n" <<
		"\txx                                       xx\n" <<
		"\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << std::endl;
	system("pause");

}

void VideoPoker::welcome() const
{
	std::cout << "\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n" <<
		"\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n" <<
		"\txx            Jacks or better!         xx\n" <<
		"\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n" <<
		"\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << std::endl << std::endl;

	std::cout << "\tHow to play:\n";
	std::cout << "\t============\n";
	std::cout << "\tWelcome to Jacks or better, the goal of Jacks or better is well....to get a pair of jacks or better!!\n" <<
		"\tYou must aim to get one of the combinations of cards to get a payout.\n" <<
		"\tThe combinations are listed as following: A two pair - any pair of two different cards.\n" <<
		"\tA full house - a pair with a three of a kind. A four of a kind - any card that you have four of.\n" <<
		"\tThree of a kind - any card that you have three of. A straight - 5 cards with face values numerically in order\n" <<
		"\tA flush - five cards of the same suit. A straight flush - a straight and flush combo!\n" <<
		"\tLast but not least is a royal flush - a 10, jack, queen, king and ace of the same suit!\n\n";


}

void VideoPoker::playOptions() const
{
	std::cout << "\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n" <<
		"\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n" <<
		"\txxx                                      xxx\n" <<
		"\txxx       1) View the pay table          xxx\n" <<
		"\txxx                                      xxx\n" <<
		"\txxx       2) Play Jacks or better!       xxx\n" <<
		"\txxx                                      xxx\n" <<
		"\txxx       3) Quit                        xxx\n" <<
		"\txxx                                      xxx\n" <<
		"\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n" <<
		"\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
}

void VideoPoker::game()
{

	system("cls");

	Deck deck;
	Hand hand;

	deck.shuffle();
	while (hand.size() != 5) //makes the hand
		hand.addCard(deck.draw());


	drawNewCards(hand); //choose cards to hold or redraw 


	for (int i = 0; i != choices.size(); i++)
	{
		if (choices[i] != 0)
			hand.redrawCard(choices[i], deck.draw()); //redraws any cards the player wanted
	}

	std::cout << hand << std::endl;

	hand.score(); //checks to see if the player won anything

	outcome(hand); //pays out the money if they did win
}

void VideoPoker::initPayouts() // fills the payout map with payouts and amount won
{
	std::pair<PokerHand, int> pair(PokerHand::PAIR, 1);
	std::pair<PokerHand, int> twoPair(PokerHand::TWOPAIR, 2);
	std::pair<PokerHand, int> threeOfAKind(PokerHand::THREEOFAKIND, 3);
	std::pair<PokerHand, int> straight(PokerHand::STRAIGHT, 4);
	std::pair<PokerHand, int> flush(PokerHand::FLUSH, 6);
	std::pair<PokerHand, int> fullHouse(PokerHand::FULLHOUSE, 9);
	std::pair<PokerHand, int> fourOfAKind(PokerHand::FOUROFAKIND, 25);
	std::pair<PokerHand, int> straightFlush(PokerHand::STRAIGHTFLUSH, 50);
	std::pair<PokerHand, int> royalFlush(PokerHand::ROYALFLUSH, 250);

	_payout.insert(pair);
	_payout.insert(twoPair);
	_payout.insert(threeOfAKind);
	_payout.insert(straight);
	_payout.insert(flush);
	_payout.insert(fullHouse);
	_payout.insert(fourOfAKind);
	_payout.insert(straightFlush);
	_payout.insert(royalFlush);
}



void VideoPoker::drawNewCards(Hand hand) // draws new cards
{
	int choice = 1; 

	while (choice != 0)
	{
		std::cout << hand << std::endl;
		std::cout << "choose a card if you would like to redraw and press enter (0 to continue): ";
		std::cin >> choice;



		if (choice < 0 || choice > hand.size() || std::cin.fail())
		{
			std::cout << "enter a valid card choice" << std::endl;
			std::cin.clear();
			std::cin.ignore();
			system("pause");
		}
		else if (choice != 0)
		{

			hand.toggle(choice); // switches between cards

			int count = std::count(choices.begin(), choices.end(), choice); 

			if (count > 0) 
			{
				for (int i = 0; i < choices.size(); i++)
				{
					if (choices[i] == choice)
						choices.erase(choices.begin() + i);
				}
			}
			else	
				choices.push_back(choice);
		}
		system("cls");
	}
	system("cls");
}

void VideoPoker::outcome(Hand hand)
{
	auto end = hand._payoutHands.end();
	end--;
	for (auto h : hand._payoutHands) //checks the hands for a win
	{
		auto p = _payout.begin();

		if (h.second == true)
		{
			while (p->first != h.first) // matches the amount with the hand
			p++;

			std::cout << "You got a " << getPokerHandName(h.first) << "! You won " << p->second << " credits!" << std::endl;
			credits = credits + p->second;
			system("pause");
			break;
		}
		else if (h.first == end->first) // checks for no matches
		{
			std::cout << "I'm sorry you lost, please try again!" << std::endl;
			system("pause");
		}
	}
}