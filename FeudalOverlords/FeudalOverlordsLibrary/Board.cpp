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
	assert(cityTex.loadFromFile("../../Assets/Textures/CityTex.png"));
	assert(dirtTex.loadFromFile("../../Assets/Textures/DirtTex.png"));
	assert(grassTex.loadFromFile("../../Assets/Textures/GrassTex.png"));
	assert(mountainTex.loadFromFile("../../Assets/Textures/MountainTex.png"));

	int maxTroops = 1000;
	int maxMoney = 1000;
	int nbrPoints = 40;
	vector<int> indexCapitals(players.size());
	for (int i = 0; i < players.size(); i++)
	{
		indexCapitals.push_back(rng(0, nbrPoints));
	}
	auto diagram = generateTerrainDiagram(nbrPoints, pair<int, int>(boardWidth, boardHeight));
	for (int i = 0; i < diagram.getFaces().size(); i++)
	{
		TerritoryType type = countryside;
		for (auto indexCap : indexCapitals)
		{
			if (i == indexCap)
			{
				type = capital;
			}
		}
		int troops = rng(0, maxTroops);
		int money = rng(0, maxMoney) * 1000;
		shared_ptr<Lord> owner = make_shared<AI>(AI((AIGoal)(rand() % endAIGoal), vector<int> { rand() % 100 }));
		if (type == capital)
		{
			troops /= 2;
			money *= 2;
			owner = players[0]; // make_shared<Player>(players[0]);
		}
		// we have to convert the face to a VertexArray
		auto face = diagram.getFaces()[i];
		vector<sf::Vector2f> points;
		auto halfedge = face.outerComponent;
		auto startedge = face.outerComponent;
		while (halfedge != nullptr && halfedge != startedge)
		{
			auto x = halfedge->origin->point.x;
			auto y = halfedge->origin->point.y;
			sf::Vector2f coord(x, y);
			if (find(points.begin(), points.end(), coord) == points.end())
			{
				points.push_back(coord);
			}
			halfedge = halfedge->next;
		}

		auto shape = sf::VertexArray();
		for (auto p : points)
		{
			shape.append(sf::Vertex(p));
		}
		territories.push_back(make_unique<Territory>(Territory(Resource(money, ResourceType::money), Resource(troops, ResourceType::military), type, owner, shape)));

	}

	/*
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
	}*/
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

unique_ptr<sf::Drawable> Board::display(Window& window)
{
	// resize the vertex array to fit the level size
	board_vertices.setPrimitiveType(sf::TriangleFan);
	for (int j = 0; j < BOARD_HEIGHT; j++)
	{
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			int textureNumber = (territories[i + j * BOARD_WIDTH]->getType() == countryside) ? rand() % 3 : 3;
			
			sf::RenderStates states;
			sf::Transform trans;
			trans = trans.Identity;
			trans.translate(i*(window.dimensions.first / TILE_SIZE), j*(window.dimensions.second / TILE_SIZE));
			trans.scale((window.dimensions.first / TILE_SIZE), (window.dimensions.second / TILE_SIZE));
			states.transform = trans;
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
				abort();
				break;
			}
			territories[i + j * BOARD_WIDTH]->display(window, states);
		}
	}
	return make_unique<sf::VertexArray>(board_vertices);
}

map<shared_ptr<Lord>, int> Board::territoryCount()
{
	map<shared_ptr<Lord>, int> res_map;
	for (auto& territory : territories)
	{
		res_map[territory->getOwner()] ++;
	}
		return res_map;
}

mygal::Diagram<double> Board::generateTerrainDiagram(int nbrPoints, pair<int,int> dimensions)
{
	// Generate some points
	auto points = std::vector<mygal::Vector2<double>>();
	double margin = 5; // is used to avoid generating points too close to the borders of the window
	for (int i = 0; i < nbrPoints; i++)
	{
		points.push_back(mygal::Vector2<double>(rng(margin, dimensions.first-margin),
			rng(margin, dimensions.second-margin)));
	}
	// Initialize an instance of Fortune's algorithm
	auto algorithm = mygal::FortuneAlgorithm<double>(points);
	// Construct the diagram
	algorithm.construct();
	// computeLloydRelaxation()
	// Bound the diagram
	algorithm.bound(mygal::Box<double>{margin, margin,
		(double) dimensions.first - margin, (double) dimensions.second - margin});
	// Get the constructed diagram
	auto diagram = algorithm.getDiagram();
	// Compute the intersection between the diagram and a box
	diagram.intersect(mygal::Box<double>{0.0, 0.0, (double) dimensions.first, (double) dimensions.second});
	// we return the list of Face
	return diagram;
}