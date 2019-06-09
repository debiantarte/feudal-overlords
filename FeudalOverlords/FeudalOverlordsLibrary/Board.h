#pragma once
#include <vector>
#include <memory>
#include "Displayable.h"
#include "Territory.h"
#include "Player.h"
#include "Window.h"
#include "include/MyGAL/FortuneAlgorithm.h"
#include "include/MyGAL/Diagram.h"

#define BOARD_HEIGHT	10
#define BOARD_WIDTH		10
#define TILE_SIZE		10

using namespace std;

class Board :
	public Displayable
{
public:
	Board(vector<shared_ptr<Player>>);
	Board(vector<shared_ptr<Player>>, int, int);
	//~Board();
	virtual unique_ptr<sf::Drawable> display(Window&) override;
	map<shared_ptr<Lord>, int> territoryCount();
	vector<unique_ptr<Territory>> territories;
	mygal::Diagram<double> generateTerrainDiagram(int, pair<int, int>);
private:
	sf::VertexArray board_vertices;
	sf::Texture cityTex;
	sf::Texture dirtTex;
	sf::Texture grassTex;
	sf::Texture mountainTex;
};

