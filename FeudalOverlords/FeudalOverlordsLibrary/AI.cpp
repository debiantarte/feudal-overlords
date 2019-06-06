#include "stdafx.h"
#include "AI.h"
#include <random>

/*
 * helper function to generate random approbation
 */
double rng(int const max)
{
	static std::random_device rd;
	static std::default_random_engine engine(rd());
	// do a uniform distribution on closed interval [0.0, max]
	std::uniform_real_distribution<> distribution(0.0, std::nextafter(max, std::numeric_limits<double>::max()));
	return distribution(engine);
}


AI::AI()
{
	this->goal = (AIGoal) (rand() % (endAIGoal - 1));
	for (int i = 0; i < endPsyTraits; i++)
	{
		this->psychology.push_back(rand() % 100); // psychological values will be between 0 and 100
	}
}

AI::AI(AIGoal goal_, vector<int> psyche) :
	goal(goal_),
	psychology(psyche)
{
}

/*
AI::~AI()
{
}
*/

/**
	Approve function returns a double
	It is for now random, based on the psyche traits
*/
double AI::approve()
{
	double result = 0;
	for (int i = 0; i < endPsyTraits; i++)
	{
		result += rng((float) psychology[i]);
	}
	return result/endPsyTraits;
}

/**
	rebel method, used when the approval is too low (the threshold depends on the goal of the AI) :
	  * independance : at least 50
	  * winWithOverlord : at least 25
	WIP
*/
bool AI::rebel(double approval)
{
	bool isRebellious;
	if (goal == independance)
	{
		isRebellious = approval < 50;
	}
	else if (goal == winWithOverlord)
	{
		isRebellious = approval < 25;
	}
	if (not(isRebellious))
	{
		return false;
	}
}

unique_ptr<sf::Drawable> AI::display()
{
	// placeholder
	unique_ptr<sf::Drawable> shape = make_unique<sf::RectangleShape>(sf::RectangleShape(sf::Vector2f(120.F, 50.F)));
	return move(shape);
	// for all territories under the control of the AI, make them independant
	// vector<unique_ptr> territories;
	// for (auto t: territories)
	// {
	//     t->owner = this;
	// }
	return true;
}

vector<int> AI::getPsychology()
{
	return psychology;
}

AIGoal AI::getGoal()
{
	return goal;
}


void AI::display()
{
	return;
}