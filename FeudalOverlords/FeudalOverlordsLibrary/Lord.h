#pragma once
#include "Displayable.h"
#include <vector>

class Lord :
	public Displayable
{
public:
	Lord();
	~Lord();
	virtual string getName() = 0;
};

