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
	int capital_x = BOARD_WIDTH / 2 + rng(-1, 1);
	int capital_y = BOARD_HEIGHT / 2 + rng(-1, 1);
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			TerritoryType type = (i == capital_x && j == capital_y) ? capital : countryside;
			if (type == capital)
			{
				std::cout << "Found the capital! x: " << i << "; y: " << j << std::endl;
			}
			int troops = rng(0, BOARD_HEIGHT + j + BOARD_WIDTH + i) * 1000;
			int money = rng(0, BOARD_HEIGHT - j + BOARD_WIDTH - i) * 1000;
			shared_ptr<Lord> owner = make_shared<AI>(AI((AIGoal)(rand() % endAIGoal), vector<int> { rand() % 100 }));
			if (type == capital)
			{
				troops /= 2;
				money *= 2;
				owner = players[0]; // make_shared<Player>(players[0]);
				std::cout << "Hello !" << std::endl;
			}
			territories.push_back(make_unique<Territory>(Territory(Resource(money, ResourceType::money), Resource(troops, ResourceType::military), type, owner)));
			if (territories[i + j].get()->getType() == capital)
			{
				std::cout << "Yolo !" << std::endl;
			}
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
	std::cout << "number of territories :" << territories.size() << std::endl;
	int debug = 0;
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			/*
			int textureNumber;
			if (territories[i + j]->getType() == capital)
			{
				textureNumber = 3;
				std::cout << "The capital ! finally !" << std::endl;
			}
			else
			{
				textureNumber = 2;
			}
			*/
			int textureNumber = (territories[i + j]->getType() == countryside) ? rand() % 3 : 3;
			
			sf::RenderStates states;
			sf::Transform trans;
			trans = trans.Identity;
			trans.translate(i*(win.dimensions.first / TILE_SIZE), j*(win.dimensions.second / TILE_SIZE));
			trans.scale((win.dimensions.first / TILE_SIZE), (win.dimensions.second / TILE_SIZE));
			states.transform = trans;
			debug++;
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
				std::cout << "I'm a capital !" << std::endl;
				break;
			default:
				abort();
				break;
			}
			territories[i + j * BOARD_WIDTH]->display(win, states);
		}
	}
	//win.display();
	std::cout << debug << std::endl;
	return make_unique<sf::VertexArray>(board_vertices);
}
