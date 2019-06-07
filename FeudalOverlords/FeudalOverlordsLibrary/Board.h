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
	Board(vector<shared_ptr<Player>>, Window&);
	//~Board();
	virtual unique_ptr<sf::Drawable> display();
	void onClick(sf::Mouse::Button);
private:
	vector<unique_ptr<Territory>> territories;
	sf::VertexArray board_vertices;
	sf::Texture cityTex;
	sf::Texture dirtTex;
	sf::Texture grassTex;
	sf::Texture mountainTex;
	Window& win;
};

