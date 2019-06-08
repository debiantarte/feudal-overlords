#pragma once

#include "Lord.h"
#include "Resource.h"
#include "Window.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

using namespace std;

enum TerritoryType {
	capital,
	countryside,
	grasslands,
	highlands,
	endTerritoryType
};

class Territory //: public sf::Shape (aborted for now) // this inheritance allows us e.g. to use getGlobalBounds to ease mouse handling
{
public:
	Territory(Resource money, Resource miliary, TerritoryType type, shared_ptr<Lord> owner);
	~Territory();
	void resetResources();
	void display(Window&, const sf::RenderStates&);
	TerritoryType getType() const;
	void onClick(sf::Vector2f, int, int, int, sf::Mouse::Button);
private:
	Resource money;
	Resource military;
	TerritoryType type;
	shared_ptr<Lord> owner;
	sf::VertexArray shape;
};
