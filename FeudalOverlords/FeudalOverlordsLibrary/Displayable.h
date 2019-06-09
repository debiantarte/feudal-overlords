#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Window.h"

using namespace std;

class Displayable
{
public:
	Displayable();
	virtual unique_ptr<sf::Drawable> display(Window&) = 0;
	~Displayable();
};

