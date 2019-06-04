#pragma once
#include <vector>
#include "Displayable.h"
#include "Territory.h"

#define BOARD_HEIGHT 10
#define BOARD_WIDTH 10

using namespace std;

class Board :
	public Displayable
{
public:
	Board();
	//~Board();
private:
	vector<Territory> territories;
};

