#include "stdafx.h"
#include "Territory.h"
#include <cassert>
#include <memory>

using namespace std;

Territory::Territory(Resource money, Resource military, TerritoryType type, shared_ptr<Lord> owner) : money(money), military(military),
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

sf::VertexArray Territory::getShape() // Placeholder
{
	sf::VertexArray quad(sf::Quads, 4);
	quad[0].position = sf::Vector2f(0.0, 0.0);
	quad[1].position = sf::Vector2f(1.0, 0.0);
	quad[2].position = sf::Vector2f(1.0, 1.0);
	quad[3].position = sf::Vector2f(0.0, 1.0);
	return quad;
}

TerritoryType Territory::getType() const
{
	return type;
}