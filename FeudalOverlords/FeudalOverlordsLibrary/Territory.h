#pragma once

#include "Lord.h"
#include "Resource.h"

enum TerritoryType {
	capital,
	countryside
};

class Territory
{
public:
	Territory(Resource money, Resource miliary, TerritoryType type, Lord& owner);
	~Territory();
	void resetResources();
private:
	Resource money;
	Resource military;
	TerritoryType type;
	Lord& owner;
};
<<<<<<< HEAD
=======

enum TerritoryType {
	capital,
	countryside,
	endTerritoryType
};
>>>>>>> 728a338f082d9f5356e1c6e7e355eb5bde3425b4
