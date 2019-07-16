#pragma once
#include <vector>
#include <memory>
#include "Displayable.h"
#include "Territory.h"
#include "Player.h"
#include "Window.h"
#include "include/MyGAL/FortuneAlgorithm.h"
#include "include/MyGAL/Diagram.h"

#define CAPITAL_TROOPS  500
#define CAPITAL_MONEY	800
#define NBR_LLOYD_RELAX	3

using namespace std;

class Board :
	public Displayable
{
public:
	Board(vector<shared_ptr<Player>>, int, int, int);
	//~Board();
	virtual void display(Window& window);
	void onClick(pair<int, int>, sf::Mouse::Button, Window&);
	map<shared_ptr<Lord>, int> territoryCount();
	vector<unique_ptr<Territory>> territories;
	mygal::Diagram<double> generateTerrainDiagram(std::vector<mygal::Vector2<double>>, pair<int, int>, double);
	//Territory* getSelected() const;
	//Territory* getTarget() const;
//private:
	sf::VertexArray board_vertices;
	sf::Texture cityTex;
	sf::Texture dirtTex;
	sf::Texture grassTex;
	sf::Texture mountainTex;
	Territory* selected;
	Territory* target;
	std::vector<std::vector<pair<double, double>>> adjacency_list;
	std::vector<pair<string, sf::Color>> playerColors;
};

