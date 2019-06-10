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

Board::Board(vector<shared_ptr<Player>> players, int boardWidth, int boardHeight, int nbrPoints) :
	board_vertices(sf::VertexArray())
{
	assert(cityTex.loadFromFile("../../Assets/Textures/CityTex.png"));
	assert(dirtTex.loadFromFile("../../Assets/Textures/DirtTex.png"));
	assert(grassTex.loadFromFile("../../Assets/Textures/GrassTex.png"));
	assert(mountainTex.loadFromFile("../../Assets/Textures/MountainTex.png"));

	int maxTroops = 1000;
	int maxMoney = 1000;
	vector<int> indexCapitals;
	for (size_t i = 0; i < players.size(); i++)
	{
		indexCapitals.push_back(rng(0, nbrPoints));
	}
	auto diagram = generateTerrainDiagram(nbrPoints, pair<int, int>(boardWidth, boardHeight));
	for (size_t i = 0; i < diagram.getFaces().size(); i++)
	{
		TerritoryType type = countryside;
		int intTerritory = rng(1, endTerritoryType);
		switch (intTerritory)
		{
		case 1:
			type = countryside;
			break;
		case 2:
			type = grasslands;
			break;
		case 3:
			type = highlands;
			break;
		default:
			break;
		}
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
			owner = players[0];
		}
		// we have to convert the face to a VertexArray
		auto face = diagram.getFaces()[i];
		vector<sf::Vector2f> points;
		double minx, maxx, miny, maxy;
		auto halfedge = face.outerComponent;
		auto startedge = face.outerComponent;
		int tmp = 0;
		while (halfedge != nullptr && (tmp == 0 || halfedge != startedge))
		{
			auto x = halfedge->origin->point.x;
			auto y = halfedge->origin->point.y;
			if (tmp == 0)
			{
				minx = x;
				maxx = x;
				miny = y;
				maxy = y;

			}
			if (x > maxx) maxx = x;
			if (x < minx) minx = x;
			if (y > maxy) maxy = y;
			if (y < miny) miny = y;
			sf::Vector2f coord((float)x, (float)y);
			//if (points.size() > 0 && find(points.begin(), points.end(), coord) == points.end())
			//{
				points.push_back(coord);
			//}
			halfedge = halfedge->next;
			tmp++;
		}
		// we need to compute texture coords

		auto shape = sf::VertexArray(sf::TriangleFan);
		for (auto p : points)
		{
			shape.append(sf::Vertex(p, sf::Vector2f(64*(p.x - minx) / (maxx - minx), 64*(p.y - miny) / (maxy - miny))));
		}
		territories.push_back(make_unique<Territory>(Territory(Resource(money, ResourceType::money), Resource(troops, ResourceType::military), type, owner, shape)));

	}
}

void Board::display(Window& window)
{
	for (auto& tile: territories)
	{
		sf::RenderStates states;
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

void Board::onClick(pair<int, int> mousePos, sf::Mouse::Button mb, Window& window)
{
	int posX = mousePos.first;
	int posY = mousePos.second;
	/*int width = (window.dimensions.first / TILE_SIZE);
	int height = (window.dimensions.second - 100) / TILE_SIZE;
	*/
	
	std::cout << "mouse position : X = " << posX << "; Y = " << posY << std::endl;

	for (auto& tile : territories)
	{
		if (tile->isOver(pair<int, int>(posX, posY), mb))
		{
			if (mb == sf::Mouse::Left)
			{
				if (selected != nullptr)
				{
					selected->setColor(sf::Color::White); // reset old selected's color
				}
				if (target != nullptr && target == tile.get())
				{
					target = nullptr;
				}
				selected = &*tile;
				selected->setColor(sf::Color::Blue + sf::Color::Cyan);
			}
			else if (mb == sf::Mouse::Right)
			{
				if (target != nullptr)
				{
					target->setColor(sf::Color::White); // reset old selected's color
				}
				if (selected != nullptr && selected == tile.get())
				{
					selected = nullptr;
				}
				target = &*tile;
				target->setColor(sf::Color::Red + sf::Color::Magenta);
			}
		}
	}
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
	// Bound the diagram
	algorithm.bound(mygal::Box<double>{margin, margin,
		(double) dimensions.first - margin, (double) dimensions.second - margin});
	// Get the constructed diagram
	auto diagram = algorithm.getDiagram();
	for (int i = 0; i < 10; i++) {
		diagram.computeLloydRelaxation();
	}
	// Compute the intersection between the diagram and a box
	diagram.intersect(mygal::Box<double>{0.0, 0.0, (double) dimensions.first, (double) dimensions.second});
	// we return the list of Face
	return diagram;
}
