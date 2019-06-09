#pragma once
#include <vector>
#include "Displayable.h"
#include "Territory.h"
#include "Player.h"
#include "Window.h"
#include <memory>

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
	virtual void display(Window& window);
	void onClick(int, int, sf::Mouse::Button, Window&);
	map<shared_ptr<Lord>, int> territoryCount();
	vector<unique_ptr<Territory>> territories;
private:
	sf::VertexArray board_vertices;
	sf::Texture cityTex;
	sf::Texture dirtTex;
	sf::Texture grassTex;
	sf::Texture mountainTex;
	Territory* selected;
};

