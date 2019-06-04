#pragma once
#include <vector>
#include "Displayable.h"
#include "Territory.h"

using namespace std;

class Board :
	public Displayable
{
public:
	Board();
	~Board();
private:
	vector<Territory> territories;
};

