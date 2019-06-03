#include "stdafx.h"
#include "Territory.h"


Territory::Territory(int baseMoney, int baseTroops, TerritoryType type, Lord& owner) : baseMoney(baseMoney), remainingMoney(baseMoney),
baseTroops(baseTroops), remainingTroops(baseTroops), type(type), owner(owner)
{
}


Territory::~Territory()
{
}
