#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "Displayable.h"
#include "Player.h"
#include "Board.h"
#include "Window.h"


#define NBR_POINTS	100
#define PROBA_REBEL	10

using namespace std;

enum endingCondition { // for now (milestone 1), we assume we are in turnLimit condition
	conquest,
	turnLimit,
	endEndingConditions
};

enum attackRes {
	impossible,
	victory,
	defeat,
	movement,
	endAttackRes
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

	GameManager(int nbrAIs, vector<shared_ptr<Player>>, const pair<int, int>, endingCondition);
	GameManager(int nbrAIs, vector<shared_ptr<Player>>, const pair<int, int>, endingCondition, int);

	pair<string, int> nextTurn();
	void regenTerritories();
	shared_ptr<Lord> winner();
	bool isGameFinished();
	map<shared_ptr<Lord>, int> territoryCount();
	void setTurn(int);
	void playerTurn();	
	attackRes moveTroops(Territory*, Territory*);
	attackRes attack();
	string getSelectedOwner();
	string getTargetOwner();
private:
	int finishTurn; // the last turn of the game.
	int turn; // the current turn
	endingCondition endingCond;
};

