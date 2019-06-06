#pragma once

#include "Lord.h"
#include "Resource.h"

enum TerritoryType {
	capital,
	countryside,
	endTerritoryType
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
