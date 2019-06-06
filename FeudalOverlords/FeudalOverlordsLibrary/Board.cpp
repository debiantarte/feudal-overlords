#include "stdafx.h"
#include "Board.h"
#include "AI.h"
#include "Resource.h"
#include <random>

/*
 * helper function to generate random territories
 */
int rng(int const min, int const max)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(min, max);
	return distribution(engine);
}

Board::Board(vector<Player> players)
{
	// we want to place the capital somewhere in the middle
	int capital_x = BOARD_WIDTH / 2 + rng(-1, 1);
	int capital_y = BOARD_HEIGHT / 2 + rng(-1, 1);
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; i < BOARD_HEIGHT; i++)
		{
<<<<<<< HEAD
			TerritoryType type = countryside;
			if (i == capital_x && j == capital_y)
			{
				type = capital;
			}
			int troops = rng(0, BOARD_HEIGHT / 2 + j + BOARD_WIDTH / 2 + i) * 1000;
			int money = rng(0, BOARD_HEIGHT / 2 - j + BOARD_WIDTH / 2 - i) * 1000;
			shared_ptr<Lord> owner = make_shared<Lord>(AI((AIGoal)(rand() % endAIGoal), vector<int> { rand() % 100 }));
			if (type == capital)
			{
				troops /= 2;
				money *= 2;
				owner = make_shared<Lord>(players[0]);
			}
			territories.push_back(Territory(Resource(money, ResourceType::money), Resource(troops, ResourceType::military), type, owner));
=======
			int troops = rng(BOARD_HEIGHT / 2 + j + BOARD_WIDTH / 2 + i) * 1000;
			int money = rng(BOARD_HEIGHT / 2 - j + BOARD_WIDTH / 2 - i) * 1000;
			territories.push_back(Territory(money, troops, (TerritoryType) (rand() % endTerritoryType), nullptr)); // TODO
>>>>>>> develop
		}
	}
}

/*
Board::~Board()
{
}
*/

unique_ptr<sf::Drawable> Board::display()
{

}