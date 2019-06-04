#include "stdafx.h"
#include "GameManager.h"
#include <cassert>




GameManager::GameManager(int nbrPlayers, int nbrAIs) : nbrPlayers(nbrPlayers), nbrAIs(nbrAIs)
{
	assert(nbrPlayers >= 0);
	assert(nbrAIs >= 0);
}

GameManager::~GameManager()
{
}

void GameManager::nextTurn()
{
	// take all the players and iterate through them
	// then the AIs
}

bool GameManager::isGameWon()
{
	// TODO
	return false;
}
