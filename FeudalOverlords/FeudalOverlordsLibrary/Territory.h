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
	endTerritoryType
};

class Territory
{
public:
	Territory(Resource money, Resource miliary, TerritoryType type, shared_ptr<Lord> owner, sf::VertexArray);
	~Territory();
	void resetResources();
	void display(Window&, const sf::RenderStates&);
	TerritoryType getType() const;
	shared_ptr<Lord> getOwner();
	void setOwner(shared_ptr<Lord>);
private:
	Resource money;
	Resource military;
	TerritoryType type;
	shared_ptr<Lord> owner;
	sf::VertexArray shape;
};
