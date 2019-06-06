#include "stdafx.h"
#include "GameManager.h"
#include <cassert>




GameManager::GameManager(int nbrAIs, vector<shared_ptr<Player>> players) :
	nbrPlayers(players.size()), nbrAIs(nbrAIs), players(players), board(players)
{
	assert(nbrAIs >= 0);
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

