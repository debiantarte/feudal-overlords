#pragma once

#include "Lord.h"
#include "Resource.h"
#include <SFML/Graphics.hpp>
#include <memory>

using namespace std;

enum TerritoryType {
	capital,
	countryside
};

class Territory
{
public:
	Territory(Resource money, Resource miliary, TerritoryType type, shared_ptr<Lord> owner);
	~Territory();
	void resetResources();
	sf::VertexArray getShape();
	TerritoryType getType() const;
private:
	Resource money;
	Resource military;
	TerritoryType type;
	shared_ptr<Lord> owner;
};
