#include "stdafx.h"
#include "GameManager.h"
#include <cassert>




GameManager::GameManager(int nbrPlayers, int nbrAIs) : nbrPlayers(nbrPlayers), nbrAIs(nbrAIs)
{
	assert(nbrPlayers >= 0);
	assert(nbrAIs >= 0);
	for (int i = 0; i < nbrPlayers; i++)
	{
		players.push_back(make_unique<Player>());
	}
}

void GameManager::nextTurn()
{
	// take all the players and iterate through them
	// then the AIs
	for (auto& player: players)
	{
		// it's player's turn
		// we should display that it's their turn
		// then act depending on their input
		// select territory : left click
		// to move troop or resources to another territory : right click on the destination territory
	}
}

bool GameManager::isGameWon()
{
	// TODO
	return false;
}
