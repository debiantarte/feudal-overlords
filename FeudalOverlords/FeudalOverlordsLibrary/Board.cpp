#include "stdafx.h"
#include "Board.h"
#include "AI.h"
#include "Resource.h"
#include <random>
#include <cassert>

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

Board::Board(vector<Player> players, Window& win_) :
	board_vertices(sf::VertexArray()), win(win_)
{
	assert(cityTex.loadFromFile("CityTex.png"));
	assert(dirtTex.loadFromFile("DirtTex.png"));
	assert(grassTex.loadFromFile("GrassTex.png"));
	assert(mountainTex.loadFromFile("MountainTex.png"));
	// we want to place the capital somewhere in the middle
	int capital_x = BOARD_WIDTH / 2 + rng(-1, 1);
	int capital_y = BOARD_HEIGHT / 2 + rng(-1, 1);
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			TerritoryType type = countryside;
			if (i == capital_x && j == capital_y)
			{
				type = capital;
			}
			int troops = rng(0, BOARD_HEIGHT / 2 + j + BOARD_WIDTH / 2 + i) * 1000;
			int money = rng(0, BOARD_HEIGHT / 2 - j + BOARD_WIDTH / 2 - i) * 1000;
			shared_ptr<Lord> owner = make_shared<AI>(AI((AIGoal)(rand() % endAIGoal), vector<int> { rand() % 100 }));
			if (type == capital)
			{
				troops /= 2;
				money *= 2;
				owner = make_shared<Player>(players[0]);
			}
			territories.push_back(make_unique<Territory>(Territory(Resource(money, ResourceType::money), Resource(troops, ResourceType::military), type, owner)));
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
	// resize the vertex array to fit the level size
	board_vertices.setPrimitiveType(sf::TriangleFan);
	for (auto& tile : territories)
	{
		// get the current tile number
		int textureNumber = (tile->getType() == countryside) ? rand() % 3 : 3;
		// find its position in the tileset texture
		int texturePos = textureNumber * 64;

		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			for (int j = 0; j < BOARD_HEIGHT; j++)
			{
				sf::RenderStates states;
				states.transform.translate(i*TILE_SIZE, j*TILE_SIZE);
				states.transform.scale(TILE_SIZE, TILE_SIZE);
				switch (textureNumber)
				{
				case 0:
					states.texture = &dirtTex;
					break;
				case 1:
					states.texture = &grassTex;
					break;
				case 2:
					states.texture = &mountainTex;
					break;
				case 3:
					states.texture = &cityTex;
					break;
				default:
					break;
				}
				territories[i + j * BOARD_WIDTH]->display(win, states);
			}
		}
	}

	return make_unique<sf::VertexArray>(board_vertices);
}
