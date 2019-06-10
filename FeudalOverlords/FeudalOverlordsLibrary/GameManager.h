#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "Displayable.h"
#include "Player.h"
#include "Board.h"
#include "Window.h"


#define NBR_POINTS 100

using namespace std;

enum endingCondition { // for now (milestone 1), we assume we are in turnLimit condition
	conquest,
	turnLimit,
	endEndingConditions
};

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
	int currentPlayerId; // the index of the current player in the vector players

	GameManager(int nbrAIs, vector<shared_ptr<Player>>, const pair<int, int>);
	GameManager(int nbrAIs, vector<shared_ptr<Player>>, const pair<int, int>, int);

	void nextTurn(); // TODO
	shared_ptr<Lord> winner();
	bool isGameFinished();
	map<shared_ptr<Lord>, int> territoryCount();
	void setTurn(int);
	void playerTurn();	
	void moveTroops(Territory*, Territory*);
	void attack();
	string getSelectedOwner();
	string getTargetOwner();
private:
	int finishTurn; // the last turn of the game.
	int turn; // the current turn
	endingCondition endingCond;
};

