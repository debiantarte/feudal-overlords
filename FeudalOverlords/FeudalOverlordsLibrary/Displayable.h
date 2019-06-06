#pragma once
#include <SFML/Graphics.hpp>

class Displayable
{
public:
	Displayable();
	virtual unique_ptr<sf::Drawable> display() = 0;
	~Displayable();
};

