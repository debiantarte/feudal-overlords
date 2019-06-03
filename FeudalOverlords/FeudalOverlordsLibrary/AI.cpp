#include "stdafx.h"
#include "AI.h"
#include <random>

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
