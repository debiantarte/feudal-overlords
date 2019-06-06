#pragma once
#include <vector>
#include "Displayable.h"
#include "Territory.h"
#include "Player.h"

#define BOARD_HEIGHT	10
#define BOARD_WIDTH		10
#define TILE_SIZE		10

using namespace std;

class Board :
	public Displayable
{
public:
	Board(vector<Player>);
	//~Board();
	virtual unique_ptr<sf::Drawable> display();
private:
	vector<Territory> territories;
};

