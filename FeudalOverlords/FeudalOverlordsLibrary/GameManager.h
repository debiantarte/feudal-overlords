#pragma once
#include <vector>
#include <memory>
#include "Displayable.h"
#include "Player.h"
#include "Board.h"

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
	vector<shared_ptr<Player>> players;
	Board board;

	GameManager(int nbrAIs, vector<shared_ptr<Player>>);

	void nextTurn(); // TODO
	bool isGameWon(); // TODO
private:
};

