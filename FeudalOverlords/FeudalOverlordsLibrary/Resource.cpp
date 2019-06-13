#include "stdafx.h"
#include "Resource.h"
#include <cassert>


Resource::Resource(int maxAmount, ResourceType type) : maxAmount(maxAmount), currentAmount(maxAmount), type(type)
{
}


Resource::~Resource()
{
}

void Resource::setCurrentAmount(int amount)
{
	assert(amount <= this->maxAmount);
	this->currentAmount = amount;
}

void Resource::resetAmount()
{
	currentAmount = maxAmount;
}

ResourceType Resource::getType()
{
	return type;
}

void Resource::setAmount(int amount)
{
	currentAmount = amount;
}

int Resource::getAmount() const
{
	return currentAmount;
}

int Resource::getMaxAmount() const
{
	return maxAmount;
}
