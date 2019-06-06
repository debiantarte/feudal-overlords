#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

using namespace std;

class Displayable
{
public:
	Displayable();
	virtual unique_ptr<sf::Drawable> display() = 0;
	~Displayable();
};

