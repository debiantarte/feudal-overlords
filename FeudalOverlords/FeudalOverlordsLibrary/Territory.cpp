#include "stdafx.h"
#include "Territory.h"
#include <cassert>
#include <memory>
#include <iostream>

using namespace std;

Territory::Territory(Resource money, Resource military, TerritoryType type, shared_ptr<Lord> owner) : money(money), military(military),
type(type), owner(owner)
{
	assert(money.getType() == ResourceType::money);
	assert(military.getType() == ResourceType::military);
	shape.append(sf::Vertex(sf::Vector2f(0.0, 0.0)));
	shape.append(sf::Vertex(sf::Vector2f(0.0, 1.0)));
	shape.append(sf::Vertex(sf::Vector2f(1.0, 1.0)));
	shape.append(sf::Vertex(sf::Vector2f(1.0, 0.0)));
}

Territory::~Territory()
{
}

void Territory::resetResources()
{
	this->military.resetAmount();
	this->money.resetAmount();
}

TerritoryType Territory::getType() const
{
	if (type == capital)
	{
		std::cout << "That's a capital !" << std::endl;
	}
	return type;
}

void Territory::display(Window& win, const sf::RenderStates& states)
{
	shape.setPrimitiveType(sf::TriangleFan);
	win.draw(shape, states);
}