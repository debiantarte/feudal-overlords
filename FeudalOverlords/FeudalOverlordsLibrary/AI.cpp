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

double AI::approve()
{
	double result = 0;
	for (int i = 0; i < endPsyTraits; i++)
	{
		result += rng(psychology[i] * 1.F);
	}
	return result;
}