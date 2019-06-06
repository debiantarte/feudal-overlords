#pragma once
#include <vector>
#include <memory>
#include "Displayable.h"
#include "Player.h"

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
	vector<unique_ptr<Player>> players;

	GameManager(int nbrPplayers, int nbrAIs);

	void nextTurn(); // TODO
	bool isGameWon(); // TODO
private:
};

