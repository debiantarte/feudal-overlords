#include "stdafx.h"
#include "Board.h"
#include "AI.h"
#include "Resource.h"
#include <random>
#include <cassert>
#include <iostream> // for debug
#include <SFML/Audio.hpp>
#include "delaunator.hpp"

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
double rng(double const min, double const max)
{
	assert(min < max);
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	std::uniform_real_distribution<> distribution(min, max);
	return distribution(engine);
}

Board::Board(vector<shared_ptr<Player>> players, int boardWidth, int boardHeight, int nbrPoints) :
	board_vertices(sf::VertexArray())
{
	bool texLoaded;
	texLoaded = cityTex.loadFromFile("../../Assets/Textures/CityTex2.png");
	assert(texLoaded);
	texLoaded = dirtTex.loadFromFile("../../Assets/Textures/DirtTex2.png");
	assert(texLoaded);
	texLoaded = grassTex.loadFromFile("../../Assets/Textures/GrassTex2.png");
	assert(texLoaded);
	texLoaded = mountainTex.loadFromFile("../../Assets/Textures/MountainTex2.png");
	assert(texLoaded);

	int maxTroops = 1000;
	int maxMoney = 1000;
	int playerNbr = 0;
	vector<sf::Color> playerColors = { sf::Color::Blue, sf::Color::Green, sf::Color::Yellow, sf::Color::Red };
	std::random_shuffle(playerColors.begin(), playerColors.end());
	vector<int> indexCapitals;
	for (size_t i = 0; i < players.size(); i++)
	{
		indexCapitals.push_back(rng(0, nbrPoints));
	}
	auto coords = std::vector<double>();
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
		sf::Color color = sf::Color(sf::Uint8(150.0), sf::Uint8(150.0), sf::Uint8(150.0));
		if (type == capital)
		{
			troops = CAPITAL_TROOPS;
			money = CAPITAL_MONEY;
			owner = players[playerNbr];
			playerNbr++;
			color = playerColors[playerColors.size() - 1];
			playerColors.pop_back(); 
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
			
			points.push_back(coord);

			halfedge = halfedge->next;
			tmp++;
		}
		// we need to compute texture coords

		auto shape = sf::VertexArray(sf::TriangleFan);
		auto center = pair<double, double>();
		for (auto p : points)
		{
			shape.append(sf::Vertex(p, sf::Vector2f(64*(p.x - minx) / (maxx - minx), 64*(p.y - miny) / (maxy - miny))));
			center.first += p.x;
			center.second += p.y;
		}
		center.first /= points.size();
		center.second /= points.size();
		territories.push_back(make_unique<Territory>(Territory(Resource(money, ResourceType::money), Resource(troops, ResourceType::military), type, owner, shape, center, color)));
		coords.push_back(center.first);
		coords.push_back(center.second);
	}
	delaunator::Delaunator d(coords);
	adjacency_list = std::vector<std::vector<pair<double, double>>>(territories.size());
	for (std::size_t i = 0; i < d.triangles.size(); i += 3) {
		auto terr0_id = -1;
		auto terr1_id = -1;
		auto terr2_id = -1;
		for (size_t j = 0; j < territories.size(); j++) {
			if (d.coords[2 * d.triangles[i]] == territories[j]->getCenter().first
				&& d.coords[2 * d.triangles[i] + 1] == territories[j]->getCenter().second) {
				terr0_id = j;
			} else if(d.coords[2 * d.triangles[i+1]] == territories[j]->getCenter().first
				&& d.coords[2 * d.triangles[i+1] + 1] == territories[j]->getCenter().second) {
				terr1_id = j;
			} else if (d.coords[2 * d.triangles[i + 2]] == territories[j]->getCenter().first
				&& d.coords[2 * d.triangles[i + 2] + 1] == territories[j]->getCenter().second) {
				terr2_id = j;
			}
		}
		assert(terr0_id != terr1_id
		&& terr0_id != terr2_id
		&& terr0_id != -1
		&& terr1_id != terr2_id
		&& terr1_id != -1
		&& terr2_id != -1);
		auto center_0 = territories[terr0_id]->getCenter();
		auto center_1 = territories[terr1_id]->getCenter();
		auto center_2 = territories[terr2_id]->getCenter();
		if (std::find(adjacency_list[terr0_id].begin(),
			adjacency_list[terr0_id].end(), center_1) == adjacency_list[terr0_id].end())
			adjacency_list[terr0_id].push_back(center_1);
		if (std::find(adjacency_list[terr0_id].begin(),
			adjacency_list[terr0_id].end(), center_2) == adjacency_list[terr0_id].end())
			adjacency_list[terr0_id].push_back(center_2);
		if (std::find(adjacency_list[terr1_id].begin(),
			adjacency_list[terr1_id].end(), center_0) == adjacency_list[terr1_id].end())
			adjacency_list[terr1_id].push_back(center_0);
		if (std::find(adjacency_list[terr1_id].begin(),
			adjacency_list[terr1_id].end(), center_2) == adjacency_list[terr1_id].end())
			adjacency_list[terr1_id].push_back(center_2);
		if (std::find(adjacency_list[terr2_id].begin(),
			adjacency_list[terr2_id].end(), center_0) == adjacency_list[terr2_id].end())
			adjacency_list[terr2_id].push_back(center_0);
		if (std::find(adjacency_list[terr2_id].begin(),
			adjacency_list[terr2_id].end(), center_1) == adjacency_list[terr2_id].end())
			adjacency_list[terr2_id].push_back(center_1);
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
		if (tile.get() != selected && tile.get() != target && selected != nullptr)
		{
			if (tile->isAdjacent(selected->getShape()))
			{
				if (tile->getOwner()->getName() == "AI")
				{
					tile->setColor(sf::Color::White);
				}
				else
				{
					tile->setColor(tile->getColor() - sf::Color(sf::Uint8(0.0), sf::Uint8(0.0), sf::Uint8(0.0), sf::Uint8(50.0)));
				}
			}
			else
			{
				tile->resetColor();
			}
		}
		else if (selected == nullptr)
		{
			tile->resetColor();
		}
		tile->display(window, states);
	}
}

void Board::onClick(pair<int, int> mousePos, sf::Mouse::Button mb, Window& window)
{
	int posX = mousePos.first;
	int posY = mousePos.second;
	
	float distance = 1000000000.0;
	Territory* nearest = nullptr;

	for (auto& tile : territories)
	{
		float xDist = tile->getCenter().first - posX;
		float yDist = tile->getCenter().second - posY;
		float relDistance = std::sqrt(xDist * xDist + yDist * yDist);
		if (relDistance <= distance && tile->isOver(pair<int, int>(posX, posY)))
		{
			distance = relDistance;
			nearest = tile.get();
		}
	}

	if (mb == sf::Mouse::Left)
	{
		if (selected != nullptr)
		{
			selected->resetColor(); // reset old selected's color
		}
		if (target != nullptr && target == nearest)
		{
			target = nullptr;
		}
		selected = nearest;
		selected->setColor(sf::Color::Blue + sf::Color::Cyan);
		sf::SoundBuffer buffer;
		if (!buffer.loadFromFile("../../Assets/Sounds/boop.ogg")) {
			cout << "trux" << endl; return;
		};
		sf::Sound sound;
		sound.setBuffer(buffer);
		sound.setPitch(2.f);
		sound.play();
	}
	else if (mb == sf::Mouse::Right)
	{
		if (target != nullptr)
		{
			target->resetColor(); // reset old selected's color
		}
		if (selected != nullptr && selected == nearest)
		{
			selected = nullptr;
		}
		target = nearest;
		target->setColor(sf::Color::Red + sf::Color::Magenta);
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
	for (int i = 0; i < 100; i++) {
		diagram.computeLloydRelaxation();
	}
	// Compute the intersection between the diagram and a box
	diagram.intersect(mygal::Box<double>{0.0, 0.0, (double) dimensions.first, (double) dimensions.second});
	// we return the list of Face
	return diagram;
}
