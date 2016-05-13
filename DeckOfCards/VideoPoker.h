//
//     Cat Fortman
//	   May 03 2016
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <unordered_map>
#include "Hand.h"

class VideoPoker
{
public:
	VideoPoker();
	~VideoPoker();

	void play();

private:

	void payTable() const;
	void welcome() const;
	void playOptions() const;
	void game();
	void initPayouts();
	void drawNewCards(Hand hand);
	void outcome(Hand hand);

private:
	int credits = 0;
	std::unordered_map<PokerHand, int> _payout;
	std::vector<int>choices;

};

