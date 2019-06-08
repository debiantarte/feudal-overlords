#include "stdafx.h"
#include "Board.h"
#include "AI.h"
#include "Resource.h"
#include <random>
#include <cassert>
#include <iostream> // for debug

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

Board::Board(vector<shared_ptr<Player>> players, Window& win_) :
	board_vertices(sf::VertexArray()), win(win_)
{
	/* TODO : check if paths are right */
	assert(cityTex.loadFromFile("../../Assets/Textures/CityTex.png"));
	assert(dirtTex.loadFromFile("../../Assets/Textures/DirtTex.png"));
	assert(grassTex.loadFromFile("../../Assets/Textures/GrassTex.png"));
	assert(mountainTex.loadFromFile("../../Assets/Textures/MountainTex.png"));
	// we want to place the capital somewhere in the middle
	int capital_x = BOARD_WIDTH / 2 + rng(-1, 1) -1;
	int capital_y = BOARD_HEIGHT / 2 + rng(-1, 1) -1;
	for (int j = 0; j < BOARD_HEIGHT; j++)
	{
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			TerritoryType type = (i == capital_x && j == capital_y) ? capital : (TerritoryType)((rand() % (endTerritoryType -1)) + 1);
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
	// resize the vertex array to fit the level size
	board_vertices.setPrimitiveType(sf::TriangleFan);
	for (int j = 0; j < BOARD_HEIGHT; j++)
	{
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			//int textureNumber = (territories[i + j * BOARD_WIDTH]->getType() == countryside) ? rand() % 3 : 3;
			Territory* tile = territories[i + j * BOARD_WIDTH].get();
			sf::RenderStates states;
			sf::Transform trans;
			trans = trans.Identity;
			trans.translate((float)i*(win.dimensions.first / TILE_SIZE), (float)j*(win.dimensions.second / TILE_SIZE));
			trans.scale((float)(win.dimensions.first / TILE_SIZE), (float)(win.dimensions.second / TILE_SIZE));
			states.transform = trans;
			switch (tile->getType())
			{
			case capital:
				states.texture = &cityTex;
				break;
			case countryside:
				states.texture = &dirtTex;
				break;
			case grasslands:
				states.texture = &grassTex;
				break;
			case highlands:
				states.texture = &mountainTex;
				break;
			default:
				abort();
				break;
			}
			tile->display(win, states);
		}
	}
	return make_unique<sf::VertexArray>(board_vertices);
}

void Board::onClick(int posX, int posY, sf::Mouse::Button mb)
{
	int width = (win.dimensions.first / TILE_SIZE);
	int mouseRelativeX = posX;
	int mouseRelativeY = posY;
	std::cout << "mouse position : X = " << mouseRelativeX << "; Y = " << mouseRelativeY << std::endl;
	bool found = false;
	Territory* target = nullptr; // just to be used as a reference, so no need to delete it (no "new" will be used)

	for (int j = 0; j < BOARD_HEIGHT && !found; j++)
	{
		for (int i = 0; i < BOARD_WIDTH && !found; i++)
		{
			// the parentheses with TILE_SIZE are placeholder until voronoi (and globally positionned vertices in each territory, which is not yet the case)
			found = territories[i + j * BOARD_WIDTH]->isOver(sf::Vector2f((float)i*width, (float)j*width), width, mouseRelativeX, mouseRelativeY, mb);
			target = territories[i + j * BOARD_WIDTH].get();
		}
	}
}