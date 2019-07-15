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

class Territory 
{
public:
	Territory(Resource money, Resource miliary, TerritoryType type, shared_ptr<Lord> owner, sf::VertexArray, pair<double, double>);
	~Territory();
	void resetResources();
	void display(Window&, const sf::RenderStates&);
	TerritoryType getType() const;
	bool isOver(pair<int, int>, sf::Mouse::Button);
	void setColor(sf::Color);
	shared_ptr<Lord> getOwner();
	void setOwner(shared_ptr<Lord>);
	void setTroops(int);
	Resource getTroops() const;
	bool isAdjacent(sf::VertexArray);
	sf::VertexArray getShape() const;
	pair<double, double> getCenter() const;
private:
	Resource money;
	Resource military;
	TerritoryType type;
	shared_ptr<Lord> owner;
	sf::VertexArray shape;
	pair<double, double> center;
};
