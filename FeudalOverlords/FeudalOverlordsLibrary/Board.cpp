#include "stdafx.h"
#include "Board.h"
#include <random>

/*
 * helper function to generate random territories
 */
int rng(int const max)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(0, max);
	return distribution(engine);
}

Board::Board()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; i < BOARD_HEIGHT; i++)
		{
			int troops = rng(BOARD_HEIGHT / 2 + j + BOARD_WIDTH / 2 + i) * 1000;
			int money = rng(BOARD_HEIGHT / 2 - j + BOARD_WIDTH / 2 - i) * 1000;
			territories.push_back(Territory(money, troops, (TerritoryType) (rand() % endTerritoryType), ));
		}
	}
}

/*
Board::~Board()
{
}
*/

