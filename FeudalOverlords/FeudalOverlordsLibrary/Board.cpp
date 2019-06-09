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

Board::Board(vector<shared_ptr<Player>> players, int boardWidth, int boardHeight) :
	board_vertices(sf::VertexArray())
{
	/* TODO : check if paths are right */
	assert(cityTex.loadFromFile("../../Assets/Textures/CityTex.png", sf::IntRect(0, 0, 64, 64)));
	assert(dirtTex.loadFromFile("../../Assets/Textures/DirtTex.png", sf::IntRect(0, 0, 64, 64)));
	assert(grassTex.loadFromFile("../../Assets/Textures/GrassTex.png", sf::IntRect(0, 0, 64, 64)));
	assert(mountainTex.loadFromFile("../../Assets/Textures/MountainTex.png", sf::IntRect(0, 0, 64, 64)));
	// we want to place the capital somewhere in the middle
	int capital_x = boardWidth / 2 + rng(-1, 1) -1;
	int capital_y = boardHeight / 2 + rng(-1, 1) -1;
	for (int j = 0; j < boardHeight; j++)
	{
		for (int i = 0; i < boardWidth; i++)
		{
			TerritoryType type = (i == capital_x && j == capital_y) ? capital : countryside;
			int troops = rng(0, boardHeight + j + boardWidth + i) * 1000;
			int money = rng(0, boardHeight - j + boardWidth - i) * 1000;
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
Board::Board(vector<shared_ptr<Player>> players) :
	Board(players, BOARD_WIDTH, BOARD_HEIGHT)
{
	
}

/*
Board::~Board()
{
}
*/

void Board::display(Window& window)
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
			trans.translate((float)i*(window.dimensions.first / TILE_SIZE), (float)j*((window.dimensions.second - 100) / TILE_SIZE));
			trans.scale((float)(window.dimensions.first / TILE_SIZE), (float)((window.dimensions.second - 100) / TILE_SIZE));
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
			tile->display(window, states);
		}
	}
}

void Board::onClick(int posX, int posY, sf::Mouse::Button mb, Window& window)
{
	int width = (window.dimensions.first / TILE_SIZE);
	int height = (window.dimensions.second - 100) / TILE_SIZE;
	
	std::cout << "mouse position : X = " << posX << "; Y = " << posY << std::endl;
	bool found = false;
	Territory* target = nullptr; // just to be used as a reference, so no need to delete it (no "new" is used)

	for (int j = 0; j < BOARD_HEIGHT || found; j++)
	{
		for (int i = 0; i < BOARD_WIDTH || found; i++)
		{
			found = territories[i + j * BOARD_WIDTH]->isOver(sf::Vector2f((float)i*width, (float)j*height), width, height, posX, posY, mb);
			if (found)
			{
				target = territories[i + j * BOARD_WIDTH].get();
			}
		}
	}
	if (target == nullptr)
	{
		return;
	}
	if (mb == sf::Mouse::Left)
	{
		if (selected != nullptr)
		{
			selected->setColor(sf::Color::White); // reset old selected's color
		}
		selected = target;
		selected->setColor(sf::Color::Blue + sf::Color::Cyan);
	}
	std::cout << "Selected a territory of type : " << selected->getType() << std::endl;
}