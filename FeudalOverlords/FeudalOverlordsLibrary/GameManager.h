#pragma once
#include "Displayable.h"
#include <vector>

using namespace std;

/**
	GameManager object
	It is instanciated when clicking on New Game
*/
class GameManager
{
public:
	int nbrPlayers;
	int nbrAIs;
	vector<Displayable> displayableObjects;
	GameManager(int nbrPplayers, int nbrAIs);
	~GameManager();

	void nextTurn(); // TODO
	bool isGameWon(); // TODO
};

