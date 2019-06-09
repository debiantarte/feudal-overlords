#pragma once
#include "Lord.h"
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

enum AIGoal
{
	independance,
	winWithOverlord,
	endAIGoal // this contains the size of the enum
};

enum PsyTraits
{
	test,
	endPsyTraits // this contains the size of the enum
};

class AI :
	public Lord
{
public:
	AI();
	AI(AIGoal, vector<int>);
	double approve();
	bool rebel(double approval); // TODO
	virtual void display(); // TODO, placeholder state
	//~AI();
	vector<int> getPsychology();
	AIGoal getGoal();
private:
	AIGoal goal;
	vector<int> psychology;
};

