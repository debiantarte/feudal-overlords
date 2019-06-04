#pragma once

#include "Lord.h"

class Territory
{
public:
	Territory(int baseMoney, int baseTroops, TerritoryType type, Lord* owner);
	~Territory();
private:
	int remainingMoney;
	int baseMoney;
	int remainingTroops;
	int baseTroops;
	TerritoryType type;
	Lord& owner;
};

enum TerritoryType {
	capital,
	countryside,
	endTerritoryType
};