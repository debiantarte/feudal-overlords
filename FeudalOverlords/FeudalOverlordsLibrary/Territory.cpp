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
	return type;
}

void Territory::display(Window& win, const sf::RenderStates& states)
{
	shape.setPrimitiveType(sf::TriangleFan);
	win.draw(shape, states);
}

// This is a pseudo-observer
void Territory::onClick(int posX, int posY, sf::Mouse::Button button)
{
	// check if mouse click was on this territory
	vector<int> y_diffs;
	vector<int> x_diffs;
	vector<int> diag_diffs;

	for (int i = 0; i < shape.getVertexCount(); i++)
	{
		sf::Vector2f p1 = shape[i].position;
		sf::Vector2f p2 = shape[(i + 1) % shape.getVertexCount()].position; // selects the next point, with a % to loop back to the first point when needed
		int y_diff = -(p2.y - p1.y);
		int x_diff = p2.x - p1.x;
		int diag_diff = -(y_diff * p1.x + x_diff * p1.y);
		y_diffs.push_back(y_diff);
		x_diffs.push_back(x_diff);
		diag_diffs.push_back(diag_diff);
	}

	vector<int> discriminers; // discriminers determine whether the point is left, on, or right of the polygon's side

	for (int i = 0; i < y_diffs.size(); i++)
	{
		int discriminer = y_diffs[i] * posX + x_diffs[i] * posY + diag_diffs[i];
		discriminers.push_back(discriminer);
	}

	bool isAlwaysLeft = std::all_of(discriminers.begin(), discriminers.end(), [](int d) {return d >= 0; });
	bool isAlwaysRight = std::all_of(discriminers.begin(), discriminers.end(), [](int d) {return d <= 0; });

	if (!isAlwaysLeft && !isAlwaysRight)
	{
		return;
	}

	switch (button)
	{
	case sf::Mouse::Button::Left:
		// check if owner is an AI or a player
		// if AI : display AI info in a tooltip that will handle further actions
		// if player : display vassal info in a tooltip
		break;
	case sf::Mouse::Button::Right:
		// todo ?
		break;
	default:
		break;
	}
}