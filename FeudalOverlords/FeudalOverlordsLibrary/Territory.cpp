#include "stdafx.h"
#include <cassert>

#include "Territory.h"


Territory::Territory(Resource money, Resource military, TerritoryType type, Lord& owner) : money(money), military(military),
type(type), owner(owner)
{
	assert(money.getType() == ResourceType::money);
	assert(military.getType() == ResourceType::military);
}


Territory::~Territory()
{
}

void Territory::resetResources()
{
	this->military.resetAmount();
	this->money.resetAmount();
}
