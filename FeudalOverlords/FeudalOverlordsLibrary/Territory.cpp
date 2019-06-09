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
bool Territory::isOver(sf::Vector2f tilePos, int width, int height, int posX, int posY, sf::Mouse::Button button)
{
	
	// first check : is it in my global bounds ? if not, it isn't anywhere near me, so do nothing
	if (!shape.getBounds().contains(sf::Vector2f((float)(posX - tilePos.x) / width, (float)(posY - tilePos.y) / height)))
	{
		return false;
	}
	// second check : it was near me, but maybe in the part of the bounding rectangle outside of the real polygon. Let's check that
	// the method comes from there : https://algorithmtutor.com/Computational-Geometry/Check-if-a-point-is-inside-a-polygon/
	vector<float> y_diffs;
	vector<float> x_diffs;
	vector<float> diag_diffs;

	for (size_t i = 0; i < shape.getVertexCount(); i++)
	{
		sf::Vector2f p1 = sf::Vector2f(shape[i].position.x * width + tilePos.x, shape[i].position.y * height + tilePos.y);
		sf::Vector2f p2 = sf::Vector2f(shape[(i + 1) % shape.getVertexCount()].position.x * width + tilePos.x, shape[(i + 1) % shape.getVertexCount()].position.y * height + tilePos.y); // selects the next point, with a % to loop back to the first point when needed
		float y_diff = -(p2.y - p1.y);
		float x_diff = p2.x - p1.x;
		float diag_diff = -(y_diff * p1.x + x_diff * p1.y);
		y_diffs.push_back(y_diff);
		x_diffs.push_back(x_diff);
		diag_diffs.push_back(diag_diff);
	}

	vector<float> discriminers; // discriminers determine whether the point is left, on, or right of the polygon's side

	for (size_t i = 0; i < y_diffs.size(); i++)
	{
		float discriminer = y_diffs[i] * posX + x_diffs[i] * posY + diag_diffs[i];
		discriminers.push_back(discriminer);
	}

	bool isAlwaysLeft = std::all_of(discriminers.begin(), discriminers.end(), [](float d) {return (d > 0 || d < FLT_EPSILON); });
	bool isAlwaysRight = std::all_of(discriminers.begin(), discriminers.end(), [](float d) {return (d < 0 || d < FLT_EPSILON); });

	if (!isAlwaysLeft && !isAlwaysRight)
	{
		return false;
	}
	std::cout << "tile position : X = " << tilePos.x << "; Y = " << tilePos.y << std::endl;
	return true;
}

void Territory::onClick(int posX, int posY, sf::Mouse::Button button)
{
	// now, depending on the input, we'll call the right function to handle it
	std::cout << "Territory clicked on : " << posX << ", " << posY << std::endl;
	switch (button)
	{
	case sf::Mouse::Button::Left:
		std::cout << "Left clicked !" << std::endl;
		// check if owner is an AI or a player
		// if AI : display AI info in a tooltip that will handle further actions
		// if player : display vassal info in a tooltip
		break;
	case sf::Mouse::Button::Right:
		std::cout << "Right clicked !" << std::endl;
		// todo ?
		break;
	default:
		break;
	}
}