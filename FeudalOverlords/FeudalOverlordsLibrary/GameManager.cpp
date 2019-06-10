#include "stdafx.h"
#include "GameManager.h"
#include <cassert>



GameManager::GameManager(int nbrAIs, vector<shared_ptr<Player>> players, pair<int, int> dimensions) :
	GameManager(nbrAIs, players, dimensions, 5)
{
}

GameManager::GameManager(int nbrAIs, vector<shared_ptr<Player>> players, pair<int, int> dimensions, int finishTurn=5) :
	nbrPlayers(players.size()), nbrAIs(nbrAIs), players(players),
	board(players, dimensions.first, dimensions.second, NBR_POINTS),
	endingCond(turnLimit), turn(0), finishTurn(finishTurn), currentPlayerId(0)
{
	assert(nbrAIs >= 0);
}

void GameManager::nextTurn()
{
	// take all the players and iterate through them
	// then the AIs
	if (board.selected != nullptr)
	{
		board.selected->setColor(sf::Color::White);
		board.selected = nullptr;
	}
	if (board.target != nullptr)
	{
		board.target->setColor(sf::Color::White);
		board.target = nullptr;
	}
	if (currentPlayerId < players.size() - 1)
	{
		currentPlayerId++;
	}
	else
	{
		turn++;
		currentPlayerId = 0;
	}
	cout << "Turn : " << players[currentPlayerId]->getName() << endl;
}

void GameManager::playerTurn()
{
	// it's player's turn
	// we should display that it's their turn
	// then act depending on their input
	// select territory : left click
	// to move troop or resources to another territory : right click on the destination territory
	auto player = players[currentPlayerId];
}


shared_ptr<Lord> GameManager::winner()
{
	if (not(isGameFinished()))
	{
		return nullptr;
	}
	// else, it is the player who has the most territories
	shared_ptr<Lord> lord = nullptr;
	int count = 0;
	for (auto& mapElement : territoryCount())
	{
		if (count < mapElement.second)
		{
			lord = mapElement.first;
			count = mapElement.second;
		}
	}
	return lord;
}

/**
	For now, it cannot act properly if the ending condition is conquest.
*/
bool GameManager::isGameFinished()
{
	// if total conquest has been achieved, or it is the last turn
	if (territoryCount().size() == 1 || endingCond == turnLimit && turn >= finishTurn)
	{
		return true;
	}
	else
	{
		return false;
	}
}

map<shared_ptr<Lord>, int> GameManager::territoryCount()
{
	return board.territoryCount();
}

void GameManager::setTurn(int turn_)
{
	turn = turn_;
}

void GameManager::moveTroops(Territory* attacker, Territory* defender)
{
	if (attacker->getOwner() == players[currentPlayerId])
	{
		int defendingTroops = defender->getTroops().getAmount();
		int attackingTroops = attacker->getTroops().getAmount();
		if (defender->getOwner() != players[currentPlayerId])
		{
			int defenseMargin = (defendingTroops - attackingTroops < 0) ? 0 : defendingTroops - attackingTroops;
			int attackingMargin = (attackingTroops - defendingTroops < 0) ? 0 : attackingTroops - defendingTroops;
			defender->setTroops(defenseMargin);
			attacker->setTroops(attackingMargin);
		}
		else
		{
			defender->setTroops(defendingTroops + attackingTroops);
			attacker->setTroops(0);
		}
	}
}

void GameManager::attack()
{
	if (board.selected != nullptr && board.target != nullptr && board.selected->getOwner() == players[currentPlayerId])
	{
		moveTroops(board.selected, board.target);
		nextTurn();
	}
}

string GameManager::getSelectedOwner()
{
	if (board.selected == nullptr)
	{
		return "";
	}
	return board.selected->getOwner()->getName();
}

string GameManager::getTargetOwner()
{
	if (board.target == nullptr)
	{
		return "";
	}
	return board.target->getOwner()->getName();
}
