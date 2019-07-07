#pragma once
#include <vector>
#include <memory>
#include "Displayable.h"
#include "Territory.h"
#include "Player.h"
#include "Window.h"
#include "include/MyGAL/FortuneAlgorithm.h"
#include "include/MyGAL/Diagram.h"

/*
#define BOARD_HEIGHT	10
#define BOARD_WIDTH		10
#define TILE_SIZE		10
*/

#define CAPITAL_TROOPS  400
#define CAPITAL_MONEY	800

using namespace std;

class Board :
	public Displayable
{
public:
	Board(vector<shared_ptr<Player>>);
	Board(vector<shared_ptr<Player>>, int, int, int);
	//~Board();
	virtual void display(Window& window);
	void onClick(pair<int, int>, sf::Mouse::Button, Window&);
	map<shared_ptr<Lord>, int> territoryCount();
	vector<unique_ptr<Territory>> territories;
	mygal::Diagram<double> generateTerrainDiagram(int, pair<int, int>);
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
};

