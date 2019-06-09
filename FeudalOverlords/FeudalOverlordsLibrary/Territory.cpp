#include "stdafx.h"
#include "Territory.h"
#include <cassert>
#include <memory>
#include <iostream>

using namespace std;

Territory::Territory(Resource money, Resource military, TerritoryType type, shared_ptr<Lord> owner, sf::VertexArray shape) :
	money(money), military(military),
type(type), owner(owner), shape(shape)
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
	return type;
}

shared_ptr<Lord> Territory::getOwner()
{
	return owner;
}

void Territory::setOwner(shared_ptr<Lord> owner_)
{
	owner = owner_;
}

void Territory::display(Window& win, const sf::RenderStates& states)
{
	shape.setPrimitiveType(sf::TriangleFan);
	win.draw(shape, states);
}