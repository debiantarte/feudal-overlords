#include "stdafx.h"
#include "Territory.h"
#include <cassert>
#include <memory>
#include <iostream>

using namespace std;

// utility to kind of override the shape's getBounds() function
// we use the fact that all our shapes are convex by design
sf::FloatRect getAccurateBounds(sf::VertexArray shape)
{
	float minx = shape[0].position.x;
	float maxx = shape[0].position.x;
	float miny = shape[0].position.y;
	float maxy = shape[0].position.y;


	for (size_t i = 0; i < shape.getVertexCount(); i++)
	{
		float x = shape[i].position.x;
		float y = shape[i].position.y;
		maxx =  (x > maxx) ? x : maxx;
		minx =  (x < minx) ? x : minx;
		maxy =  (y > maxy) ? y : maxy;
		miny =  (y < miny) ? y : miny;
	}

	sf::FloatRect res(minx, miny, maxx - minx, maxy - miny);
	return res;
}

Territory::Territory(Resource money, Resource military, TerritoryType type, shared_ptr<Lord> owner, sf::VertexArray shape, pair<double, double> center, sf::Color color) :
	money(money), military(military),
type(type), owner(owner), shape(shape), center(center), ownerColor(color)
{
	assert(money.getType() == ResourceType::money);
	assert(military.getType() == ResourceType::military);
	this->setColor(ownerColor);
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

string Territory::getTypeName() const
{
	switch (type)
	{
	case countryside:
		return "countryside";
		break;
	case highlands:
		return "highlands";
		break;
	case grasslands:
		return "grasslands";
		break;
	case capital:
		return "capital";
		break;
	default:
		return "undefined";
		break;
	}
}

shared_ptr<Lord> Territory::getOwner()
{
	return owner;
}

void Territory::setOwner(shared_ptr<Lord> owner_)
{
	owner = owner_;
}

shared_ptr<Lord> Territory::getOverlord()
{
	return overlord;
}

void Territory::setOverlord(shared_ptr<Lord> overlord)
{
	this->overlord = overlord;
}

void Territory::display(Window& win, const sf::RenderStates& states)
{
	shape.setPrimitiveType(sf::TriangleFan);
	win.draw(shape, states);
	unique_ptr<sf::Vertex> firstVertex;
	unique_ptr<sf::Vertex> secondVertex;
	for (size_t i=0; i < shape.getVertexCount(); i++)
	{
		if (i != 0)
		{
			secondVertex = move(firstVertex);
		}
		firstVertex = make_unique<sf::Vertex>(shape[i]);
		if (i != 0)
		{
			sf::VertexArray line(sf::Lines);
			line.append(*firstVertex);
			line.append(*secondVertex);
			line[0].color = sf::Color::Black;
			line[1].color = sf::Color::Black;
			win.draw(line);
		}
	}
	secondVertex = move(firstVertex);
	firstVertex = make_unique<sf::Vertex>(shape[0]);
}

// This is a pseudo-observer
bool Territory::isOver(pair<int, int> mousePos)
{

	// first check : is it in my global bounds ? if not, it isn't anywhere near me, so do nothing
	/*if (!shape.getBounds().contains(mousePos.first, mousePos.second))
	{
		return false;
	}*/

	// second check : it was near me, but maybe in the part of the bounding rectangle outside of the real polygon. Let's check that
	// the method comes from there : https://algorithmtutor.com/Computational-Geometry/Check-if-a-point-is-inside-a-polygon/
	vector<float> y_diffs;
	vector<float> x_diffs;
	vector<float> diag_diffs;

	for (size_t i = 0; i < shape.getVertexCount(); i++)
	{
		sf::Vector2f p1 = sf::Vector2f(shape[i].position.x, shape[i].position.y);
		sf::Vector2f p2 = sf::Vector2f(shape[(i + 1) % shape.getVertexCount()].position.x,
			shape[(i + 1) % shape.getVertexCount()].position.y); // selects the next point, with a % to loop back to the first point when needed
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
		float discriminer = y_diffs[i] * mousePos.first + x_diffs[i] * mousePos.second + diag_diffs[i];
		discriminers.push_back(discriminer);
	}

	bool isAlwaysLeft = std::all_of(discriminers.begin(), discriminers.end(), [](float d) {
		return d > 0;
	});
	bool isAlwaysRight = std::all_of(discriminers.begin(), discriminers.end(), [](float d) {
		return d < 0;
	});

	return isAlwaysLeft || isAlwaysRight;
}

void Territory::setColor(sf::Color col)
{
	for (size_t i = 0; i < shape.getVertexCount(); i++)
	{
		shape[i].color = col;
	}
}

void Territory::setTroops(int amount)
{
	military.setCurrentAmount(amount);
}

Resource Territory::getTroops() const
{
	return military;
}

bool Territory::isAdjacent(sf::VertexArray otherShape)
{
	// TODO : Keep it as comment until we can find a way to make it better
	/*
	int maxIter = (shape.getVertexCount() <= otherShape.getVertexCount()) ? shape.getVertexCount() : otherShape.getVertexCount();
	vector<int> commonVertices;
	commonVertices.resize(maxIter);

	for (int i = 0; i < maxIter; i++)
	{
		for (int j = 0; j < maxIter; j++)
		{
			if (shape[i].position == otherShape[j].position)
			{
				commonVertices[i] = 1;
			}
		}
		if (i > 0 && commonVertices[i - 1] && commonVertices[i])
		{
			return true;
		}
	}
	return false;
	*/
	return getAccurateBounds(shape).intersects(getAccurateBounds(otherShape));
}

sf::VertexArray Territory::getShape() const
{
	return shape;
}

pair<double, double> Territory::getCenter() const
{
	return center;
}

sf::Color Territory::getColor() const
{
	return ownerColor;
}

void Territory::resetColor()
{
	this->setColor(ownerColor);
}

void Territory::newOwnerColor(sf::Color newColor)
{
	ownerColor = newColor;
}