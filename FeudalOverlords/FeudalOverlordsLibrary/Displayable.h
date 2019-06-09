#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

using namespace std;

class Displayable
{
public:
	Displayable();
	virtual void display() = 0;
	~Displayable();
};

