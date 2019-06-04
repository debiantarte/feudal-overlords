#pragma once
#include <vector>
#include "Displayable.h"
#include "Territory.h"
#include "Player.h"

#define BOARD_HEIGHT 10
#define BOARD_WIDTH 10

using namespace std;

class Board :
	public Displayable
{
public:
	Board(vector<Player>);
	//~Board();
private:
	vector<Territory> territories;
};

