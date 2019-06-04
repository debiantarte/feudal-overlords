#pragma once

#include "Lord.h"
#include "Resource.h"

class Territory
{
public:
	Territory(Resource money, Resource miliary, TerritoryType type, shared_ptr<Lord> owner);
	~Territory();
	void resetResources();
private:
	Resource money;
	Resource military;
	TerritoryType type;
	shared_ptr<Lord> owner;
};

enum TerritoryType {
	capital,
	countryside,
	endTerritoryType
};