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
	assert(min < max);
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_int_distribution<> distribution(min, max);
	return distribution(engine);
}

Board::Board(vector<shared_ptr<Player>> players) :
	board_vertices(sf::VertexArray()), board_tileset(sf::Texture())
{
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
			int troops = rng(0, BOARD_HEIGHT + j + BOARD_WIDTH + i) * 1000;
			int money = rng(0, BOARD_HEIGHT - j + BOARD_WIDTH - i) * 1000;
			shared_ptr<Lord> owner = make_shared<AI>(AI((AIGoal)(rand() % endAIGoal), vector<int> { rand() % 100 }));
			if (type == capital)
			{
				troops /= 2;
				money *= 2;
				owner = players[0]; // make_shared<Player>(players[0]);
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
	// load the tileset texture
	assert(board_tileset.loadFromFile("TestSpriteSheet.png")); // TODO : check if the path is right

	// resize the vertex array to fit the level size
	board_vertices.setPrimitiveType(sf::Quads);
	board_vertices.resize(BOARD_WIDTH * BOARD_WIDTH * 4);

	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			// get the current tile number
			int textureNumber = (territories[i + j]->getType() == countryside) ? rand() % 3 : 3;
			// find its position in the tileset texture
			int texturePos = textureNumber * 64;

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &board_vertices[(i + j * BOARD_WIDTH) * 4];
			sf::VertexArray* territoryQuad = &(territories[i + j]->getShape());

			quad[0].position = (territoryQuad->operator[](0)).position;
		}
	}

	return make_unique<sf::VertexArray>(board_vertices);
}